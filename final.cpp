#include "include/GFinal.h"
#include "VoronoiShader.h"
#include "include/GPoint.h"
#include "include/GPath.h"
#include "include/GPathBuilder.h"
class final : public GFinal {
    std::shared_ptr<GShader> createVoronoiShader(const GPoint points[], const GColor colors[], int count) override{
        GMatrix m = {1, 0, 0,
                     0, 1, 0 };
        
        return std::unique_ptr<GShader>(new VoronoiShader(points, colors, count, m));
    }
    //Helper to draw stroke lines
    GPathBuilder strokeLine(GPathBuilder Stroke, GPoint curr, GPoint next, float width) {
        float len = width / 2.f;
        GPoint norm = {-(next.y - curr.y),(next.x - curr.x)};
        norm = norm * (1.f / sqrt(pow(norm.x, 2.f) + pow(norm.y, 2.f)));
        Stroke.moveTo(curr + norm * len);
        Stroke.lineTo(curr - norm * len);
        Stroke.lineTo(next - norm * len);
        Stroke.lineTo(next + norm * len);

        Stroke.addCircle(curr, len);
        Stroke.addCircle(next, len);
        return Stroke;
    }

    std::shared_ptr<GPath> strokePolygon(const GPoint points[], int count, float width, bool isClosed) override{
        GPathBuilder strokeBuilder;
        for(int i = 0; i < count - 1; i++) {
            GPoint curr = points[i];
            GPoint next = points[i+1];
            strokeBuilder = strokeLine(strokeBuilder, curr, next, width);
        }

        if (isClosed) {
            strokeBuilder = strokeLine(strokeBuilder, points[0], points[count - 1], width);
        }
        return strokeBuilder.detach();
    }


    
};
std::unique_ptr<GFinal> GCreateFinal() {
    return std::unique_ptr<GFinal>(new final);
}
    