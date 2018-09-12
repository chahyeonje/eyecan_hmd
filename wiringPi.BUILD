cc_library(
    name = "wiringPi",
    #srcs = glob(["lib/*.dylib"]),# for mac
    srcs = glob(["lib/*.so*"]),
    hdrs = glob(["include/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"], 
    linkstatic = 1,
)