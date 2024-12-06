#include "include/GShader.h"
#include "include/GMatrix.h"
#include "include/GBitmap.h"
#include "include/GPoint.h"
#include "utils.h"

class MyShaderS: public GShader {
private:
    GMatrix invTransform;
    GMatrix M;
public:
    MyShaderS(GMatrix m){
        M = m;
    };
    bool isOpaque() override {
        return true;
    };
    
    bool setContext(const GMatrix& ctm) override {
        auto inv = (ctm * M).invert();
        if (inv.has_value()){
            invTransform = inv.value();
            return true;
        }
        else
            return false;
        return false;
    };
    void shadeRow(int x, int y, int count, GPixel row[]) override {
        GPoint p_t = invTransform * GPoint{x + 0.5f, y + 0.5f};
        float px = p_t.x;
        float dpx = invTransform.e0().x;
    }
};