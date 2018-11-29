#include "include/network.h"
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include <math.h>
#include <regex>

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"

#include "include/camera.h"

using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;
using namespace std;

#define OUTPUT_HEIGHT 480
#define OUTPUT_WIDTH 680

//전역변수
float score;//beep음 주기를 계산하기 위한 전역변수
float seg_result[OUTPUT_WIDTH][OUTPUT_HEIGHT]; //세그멘테이션 결과를 저장하는 전역변수 224*224
//string GRAPH_PATH = "./data/frozen_inference_graph.pb";//실행파일 밑에 data폴더에 파일이 있어야함, 실행파일 위치로가서 실행하ㅐ야함
//string inputLayerName = "image_tensor:0";//수정되어야함
//vector<string> outputLayerName = {"detection_boxes:0", "detection_scores:0", "detection_classes:0", "num_detections:0"};//수정되어야함
string GRAPH_PATH = "./data/ex1.model.0.h5.pb";//실행파일 밑에 data폴더에 파일이 있어야함, 실행파일 위치로가서 실행하ㅐ야함
string inputLayerName = "input_1";//수정되어야함
vector<string> outputLayerName = {"output_node0"};//수정되어야함



string LABELS = "image_tensor:0";
string ROOTDIR = "../";


std::unique_ptr<tensorflow::Session> session;//세션 포인터
Tensor inputTensor;//인풋 텐서
std::vector<tensorflow::Tensor> outputTensors;//아웃풋 텐서
tensorflow::TensorShape shape;//인풋 쉐입
std::map<int, std::string> labelsMap;


/*
/** Read a labels map file (xxx.pbtxt) from disk to translate class numbers into human-readable labels.
 /*
Status readLabelsMapFile(const string &fileName, map<int, string> &labelsMap) {
    
    // Read file into a string
    ifstream t(fileName);
    if (t.bad())
        return tensorflow::errors::NotFound("Failed to load labels map at '", fileName, "'");
    stringstream buffer;
    buffer << t.rdbuf();
    string fileString = buffer.str();
    
    // Search entry patterns of type 'item { ... }' and parse each of them
    smatch matcherEntry;
    smatch matcherId;
    smatch matcherName;
    const regex reEntry("item \\{([\\S\\s]*?)\\}");
    const regex reId("[0-9]+");
    const regex reName("\'.+\'");
    string entry;
    
    auto stringBegin = sregex_iterator(fileString.begin(), fileString.end(), reEntry);
    auto stringEnd = sregex_iterator();
    
    int id;
    string name;
    for (sregex_iterator i = stringBegin; i != stringEnd; i++) {
        matcherEntry = *i;
        entry = matcherEntry.str();
        regex_search(entry, matcherId, reId);
        if (!matcherId.empty())
            id = stoi(matcherId[0].str());
        else
            continue;
        regex_search(entry, matcherName, reName);
        if (!matcherName.empty())
            name = matcherName[0].str().substr(1, matcherName[0].str().length() - 2);
        else
            continue;
        labelsMap.insert(pair<int, string>(id, name));
    }
    return Status::OK();
}
*/

/** 그래프 로드하는 함수, 세션오브젝트 생성*/
Status loadGraph(const string &graph_file_name,
                 unique_ptr<tensorflow::Session> *session) {
    tensorflow::GraphDef graph_def;
    Status load_graph_status =
    ReadBinaryProto(tensorflow::Env::Default(), graph_file_name, &graph_def);
    if (!load_graph_status.ok()) {
        return tensorflow::errors::NotFound("Failed to load compute graph at '",
                                            graph_file_name, "'\n");
    }
    session->reset(tensorflow::NewSession(tensorflow::SessionOptions()));
    Status session_create_status = (*session)->Create(graph_def);
    if (!session_create_status.ok()) {
        return session_create_status;
    }
    return Status::OK();
}

/** Convert Mat image into tensor of shape (1, height, width, d) where last three dims are equal to the original dims.
 */
Status readTensorFromMat(const Mat &mat, Tensor &outTensor) {
    
    auto root = tensorflow::Scope::NewRootScope();
    using namespace ::tensorflow::ops;
    
    // Trick from https://github.com/tensorflow/tensorflow/issues/8033
    float *p = outTensor.flat<float>().data();
    Mat fakeMat(mat.rows, mat.cols, CV_32FC3, p);
    mat.convertTo(fakeMat, CV_32FC3);
    /*
    auto input_tensor = Placeholder(root.WithOpName("input"), tensorflow::DT_FLOAT);
    vector<pair<string, tensorflow::Tensor>> inputs = {{"input", outTensor}};
    auto uint8Caster = Cast(root.WithOpName("uint8_Cast"), outTensor, tensorflow::DT_UINT8);
    
    // This runs the GraphDef network definition that we've just constructed, and
    // returns the results in the output outTensor.
    tensorflow::GraphDef graph;
    TF_RETURN_IF_ERROR(root.ToGraphDef(&graph));
    
    vector<Tensor> outTensors;
    unique_ptr<tensorflow::Session> session(tensorflow::NewSession(tensorflow::SessionOptions()));
    
    TF_RETURN_IF_ERROR(session->Create(graph));
    TF_RETURN_IF_ERROR(session->Run({inputs}, {"uint8_Cast"}, {}, &outTensors));
    
    outTensor = outTensors.at(0);
    */
    return Status::OK();
}


//네트워크 초기화
int initNetwork()
{
    cout <<"initNetwork() called"<<endl;
    score = 0;//스코어 초기화
    
    //그래프 읽기
    Status loadGraphStatus = loadGraph(GRAPH_PATH, &session);
    if (!loadGraphStatus.ok()) {
        cout << "loadGraph(): ERROR" << loadGraphStatus;
        return -1;
    } else
        cout << "loadGraph(): frozen graph loaded" << endl;
    
    
    //텐서 모양 정의 인풋수(1)*가로(224)*세로(224)*채널수(3)
    shape = tensorflow::TensorShape();
    shape.AddDim(1);
    shape.AddDim(OUTPUT_HEIGHT);//shape.AddDim((int64)cap.get(CAP_PROP_FRAME_HEIGHT)) 원래 이모양임
    shape.AddDim(OUTPUT_WIDTH);//이 부분 고쳐야 할 수도있음. 이때 cap은 VideoCapture cap(1);
    shape.AddDim(3);
    
    
    ////////////////////////////////////////////////////////
    
    /*
    // Load labels map from .pbtxt file
    labelsMap = std::map<int,std::string>();
    Status readLabelsMapStatus = readLabelsMapFile(tensorflow::io::JoinPath(ROOTDIR, LABELS), labelsMap);
    if (!readLabelsMapStatus.ok()) {
        LOG(ERROR) << "readLabelsMapFile(): ERROR" << loadGraphStatus;
        return -1;
    } else
        LOG(INFO) << "readLabelsMapFile(): labels map loaded with " << labelsMap.size() << " label(s)" << endl;
    
    Mat frame;
    Tensor tensor;
    std::vector<Tensor> outputs;
    double thresholdScore = 0.5;
    double thresholdIOU = 0.8;
    */
    /////////////////////////////////////////////////////////////////////
    return 0;
    
}


//세그멘테이션 결과를 결과배열에 저장한다.
void getSegmentation()
{
    
    double thresholdScore = 0.5;
    double thresholdIOU = 0.8;
    
    cout<<"getSegmentation process1\n";
    // opencv 매트릭스값을 텐서로 변환
    inputTensor = Tensor(tensorflow::DT_FLOAT, shape);
    Status readTensorStatus = readTensorFromMat(dst, inputTensor);
    if (!readTensorStatus.ok()) {
        cout << "dst->Tensor conversion failed: " << readTensorStatus;
        return;
    }
    
    
    outputTensors.clear();//아웃풋텐서 비우고
    cout<<"getSegmentation process2\n";
    //세션실행
    Status runStatus = session->Run({{inputLayerName, inputTensor}}, outputLayerName, {}, &outputTensors);
    
    if (!runStatus.ok()) {
        std::cout << runStatus.ToString() << "dddd\n";
        return;
    }else{
        cout << "Success load graph !! " << "\n";
    }
    
    // Extract results from the outputs vector
    tensorflow::TTypes<float>::Flat scores = outputTensors[0].flat<float>();
    cout<<"scores: "<<scores<<endl;
    /*
    vector<size_t> goodIdxs = filterBoxes(scores, boxes, thresholdIOU, thresholdScore);
    for (size_t i = 0; i < goodIdxs.size(); i++)
        LOG(INFO) << "score:" << scores(goodIdxs.at(i)) << ",class:" << labelsMap[classes(goodIdxs.at(i))]
        << " (" << classes(goodIdxs.at(i)) << "), box:" << "," << boxes(0, goodIdxs.at(i), 0) << ","
        << boxes(0, goodIdxs.at(i), 1) << "," << boxes(0, goodIdxs.at(i), 2) << ","
        << boxes(0, goodIdxs.at(i), 3);
     
    
    //auto output_c = outputTensors[0].~~~~~; 여기서 아웃풋 값 받으면 됨, 리쉐입해서 배열에다 넣어줘
     */
}
//score를 계산하여 전역변수 score에 저장한다.
void calculateScore()
{
    cout<<"score calculation process\n";
    
    
}
