// found on https://github.com/Profactor/cv-plot/issues/11

#pragma once

#include <CvPlot/cvplot.h>
#include <unordered_set>

namespace CvPlot {

struct LegendLabel :public Drawable {
    std::string _text;
    cv::Point _position;
    const int _fontFace = cv::FONT_HERSHEY_SIMPLEX;
    const double _fontScale = .4;
    const int _fontThickness = 1;
    cv::Scalar _color = cv::Scalar(0, 0, 0);
    void render(RenderTarget& renderTarget) override;
};

struct Legend :public Drawable {
    Axes* _parentAxes;
    int _width = 160;
    int _height = 70;
    int _margin = 0;

    std::unordered_set<Series*> blacklist;

    Legend& setWidth(int w);
    Legend& setHeigth(int h);
    Legend& setAxes(Axes& ax);

    void render(RenderTarget& renderTarget) override;
};

}