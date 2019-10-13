//
//  exception.cpp
//  liboffsetfinder64
//
//  Created by tihmstar on 09.03.18.
//  Copyright © 2018 tihmstar. All rights reserved.
//

#include <liboffsetfinder64/libgeneral/macros.h>
#include <liboffsetfinder64/libgeneral/exception.hpp>
#include <string>
#include <stdarg.h>

using namespace tihmstar;

exception::exception(int code, const char *filename, const char *err ...) :
    _code(code),
    _filename(filename),
    _err(NULL)
    {
        va_list ap = {};
        va_start(ap, err);
        vasprintf(&_err, err, ap);
        va_end(ap);
    };

const char *exception::what(){
    return _err;
}

int exception::code() const{
    return (_code << 16) | (int)(_filename.size());
}

void exception::dump() const{
    printf("[exception]:\n");
    printf("what=%s\n",_err);
    printf("code=%d\n",code());
    printf("line=%d\n",_code);
    printf("file=%s\n",_filename.c_str());
    printf("commit count=%s:\n",build_commit_count().c_str());
    printf("commit sha  =%s:\n",build_commit_sha().c_str());
}

std::string exception::build_commit_count() const {
    return VERSION_COMMIT_COUNT;
};

std::string exception::build_commit_sha() const{
    return VERSION_COMMIT_SHA;
};

exception::~exception(){
    safeFree(_err);
}
