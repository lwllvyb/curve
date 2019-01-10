/*
 * Project: curve
 * File Created: Monday, 18th February 2019 11:02:39 am
 * Author: tongguangxun
 * Copyright (c)￼ 2018 netease
 */

#ifndef CURVE_LIBCURVE_DEFINE_H
#define CURVE_LIBCURVE_DEFINE_H
#include <stdint.h>

enum FileType {
    INODE_DIRECTORY = 0,
    INODE_PAGEFILE = 1,
    INODE_APPENDFILE = 2,
    INODE_APPENDECFILE = 3,
};

enum LIBCURVE_ERROR {
    OK = 0,
    EXISTS,
    FAILED,
    DISABLEIO,
    UNKNOWN
};

typedef enum LIBCURVE_OP {
    LIBCURVE_OP_READ,
    LIBCURVE_OP_WRITE,
    LIBCURVE_OP_MAX,
} LIBCURVE_OP;

typedef void (*LibCurveAioCallBack)(struct CurveAioContext* context);

typedef struct CurveAioContext {
    off_t offset;
    size_t length;
    int ret;
    LIBCURVE_OP op;
    LIBCURVE_ERROR err;
    LibCurveAioCallBack cb;
    void* buf;
} CurveAioContext;

typedef struct FileStatInfo {
    FileType        filetype;
    uint64_t        length;
    uint64_t        ctime;
} FileStatInfo_t;

#endif  // !CURVE_LIBCURVE_DEFINE_H
