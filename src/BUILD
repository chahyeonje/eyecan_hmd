
package(
    default_visibility = ["//visibility:public"],
)


exports_files(["LICENSE"])

exports_files(["data/grace_hopper.jpg"])

load("//tensorflow:tensorflow.bzl", "tf_cc_binary")

cc_binary(   
    name = "cameratest",
    srcs = ["cameratest.cc"],
    deps = ["camera",
	   "@opencv//:opencv",
	   ],
)

tf_cc_binary(
    name = "eyecan",
    srcs = [
        "eyecan.cc",
    ],

    linkopts = [
	"-lm", 
	"-lpthread",
    ],

    copts = [
	"-I/usr/local/include/", 
	"-O3",
	],

    deps = [
	    ":camera", 
	    ":hmdcurl", 
	    ":geomagnetic", 
	    ":hmdgps", 
	    ":network", 
	    ":speaker", 
	    ":switch",
            "//tensorflow/cc:cc_ops",
            "//tensorflow/core:core_cpu",
            "//tensorflow/core:framework",
            "//tensorflow/core:framework_internal",
            "//tensorflow/core:lib",
            "//tensorflow/core:protos_all_cc",
            "//tensorflow/core:tensorflow",
    ]
)

cc_binary(
    name = "geotest",
    srcs = ["geotest.cc"],
    deps = [
	    ":geomagnetic", 
    ]
)


cc_library(
    name = "geomagnetic",
    srcs = ["geomagnetic.cc"],
    hdrs = [
        "include/geomagnetic.h",
	"include/myahrs_plus.hpp",
    ],
)

cc_library(
    name = "hmdgps",
    srcs = ["hmdgps.c"],
    deps = [
	    ":gps", 
    ],
    hdrs = [
        "include/hmdgps.h",

    ],
)


cc_import(
  name = "gps",
  hdrs = ["include/gps.h"],
  static_library = "libgps.a",
)

cc_library(
    name = "camera",
    srcs = ["camera.cc"],
    hdrs = [
        "include/camera.h",
    ],
    deps = [
	    "@opencv//:opencv",
        ]
)

cc_library(
    name = "hmdcurl",
    srcs = ["hmdcurl.cc"],
    hdrs = [
        "include/hmdcurl.h",
    ],
    linkopts = [
	"-lm", 
	"-lcrul",
    ],

)



cc_library(
    name = "network",
    srcs = ["network.cc"],
    hdrs = [
        "include/network.h",
    ],
	deps = [
           "//tensorflow/cc:cc_ops",
            "//tensorflow/core:core_cpu",
            "//tensorflow/core:framework",
            "//tensorflow/core:framework_internal",
            "//tensorflow/core:lib",
            "//tensorflow/core:protos_all_cc",
            "//tensorflow/core:tensorflow",
	    "@opencv//:opencv",
		":camera"
	]
)

cc_library(
    name = "speaker",
    srcs = ["speaker.cc"],
    hdrs = [
        "include/speaker.h",
    ],
	deps = [
	    "@opencv//:opencv",
	],
)

cc_library(
    name = "switch",
    srcs = ["switch.cc"],
    hdrs = [
        "include/switch.h",
	"@wiringPi//: wiringPi"
    ],
)
