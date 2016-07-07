#pragma once

int GetAsh(BYTE** imageBuf, int x, int y);
int TempltExcuteCl(BYTE** imageBuf0, int w, int h, int* templt, int tw, int x, int y, int cn);
void SmoothGaussCl(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h);
void SmoothMedianCl(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h, unsigned int size);
void SharpLaplacianCl(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h);
void ToTwoValue(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h, int K);
void Subtract(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h);