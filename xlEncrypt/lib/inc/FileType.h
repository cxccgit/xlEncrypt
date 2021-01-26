#ifndef _FILETYPE_H
#define _FILETYPE_H

#ifdef __cplusplus
extern "C"{
#endif

#define FILETYPE_ERROR     0x00
#define FILETYPE_ENCRYPT   0x01
#define FILETYPE_LINK      0x02
#define FILETYPE_COMPRESS  0x03
#define FILETYPE_DIRECTORY 0x04

typedef struct _filehead
{
    unsigned char fileFlag[4];
    unsigned short version;
    unsigned short fileType;
    unsigned int sizeH;
    unsigned int sizeL;
    unsigned int surplusLen;
}FileHead;

typedef struct _filecompress
{
    unsigned char fileNameLen;//文件名长度
    unsigned char * filename;//文件名
    unsigned char * table;//哈夫曼表
}FileCompress;


#ifdef __cplusplus
}
#endif

#endif//!_FILETYPE_H