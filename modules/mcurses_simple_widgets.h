#include "../mcurses_widget.h"
#include "../modules/mcurses_simple_figures.h"
#include <vector>
#define watch(x) cout<<"Var is "<<x;

namespace mcurses {

class progress_bar : public Imcurses_widget{
public:
    mcurses_simple_figures *msf;
    progress_bar(const float x, const float y, const float aspect,
                         const float width, const float height,
                         const float borderSize, mcurses_simple_figures &msf){
      this->x=x;
      this->y=y;
      this->msf = &msf;
      this->width=width;
      this->height=height;
      this->borderSize=borderSize;
    }
    progress_bar(const float x, const float y, const float aspect,
                         mcurses_simple_figures &msf, const char background)
        : progress_bar(x, y, aspect, width, height, borderSize, msf) {
      msf.screen->setBackground(background);
    }

    void show() override{ isHided = 0;}
    void hide() override{ isHided = 2;}

    void render() override{
      if(isHided == 0){
          float PX = 100 / maxValue * value / width;
          msf->drawBorder(x, y, width + (borderSize*2), height + borderSize, borderSize,
                          backgroundForegroundColor,backgroundBackgroundColor,
                          background)
              .drawRectangle(x + borderSize, y + borderSize, width, height,
                             unfilledForegroundColor, unfilledBackgroundColor,
                             unfilledBackground)
              .drawRectangle(x + borderSize, y + borderSize, float(PX), height,
                             filledForegroundColor, filledBackgroundColor,
                             filledBackground);
      }else if(isHided == 2){
            msf->drawRectangle(x, y, width + (borderSize*2), height + borderSize, backgroundForegroundColor, backgroundBackgroundColor);
      }
    }

private:
    char isHided = 1;
    float width = 1,
          height = 1,
          borderSize = 1;
    int value = 0,
        maxValue = 1,
        step = 1;
    char background = '-',
         filledBackground = '#',
         unfilledBackground = '.';
    string backgroundBackgroundColor = "WHITE",
           backgroundForegroundColor = "BLACK",
           filledBackgroundColor = "GREEN",
           filledForegroundColor = "WHITE",
           unfilledBackgroundColor = "GRAY",
           unfilledForegroundColor = "WHITE";

public:
    progress_bar PBsetValue(const float value) {
        this->value = value;
        render();
        return *this;
    }
    progress_bar PBsetMaxValue(const float maxValue) {
        this->maxValue = maxValue;
        render();
        return *this;
    }
    progress_bar PBsetStep(const float step) {
        this->step = step;
        render();
        return *this;
    }
    progress_bar PBsetBackground(const char background) {
        this->background = background;
        render();
        return *this;
    }
    progress_bar PBsetFilledBackground(const char filledBackground) {
        this->filledBackground = filledBackground;
        render();
        return *this;
    }
    progress_bar PBsetUnfilledBackground(const char unfilledBackground) {
        this->unfilledBackground = unfilledBackground;
        render();
        return *this;
    }
    progress_bar
    PBsetBackgroundBackgroundColor(const string backgroundBackgroundColor) {
        this->backgroundBackgroundColor = backgroundBackgroundColor;
        render();
        return *this;
    }
    progress_bar
    PBsetBackgroundForegroundColor(const string backgroundForegroundColor) {
        this->backgroundForegroundColor = backgroundForegroundColor;
        render();
        return *this;
    }
    progress_bar
    PBsetFilledBackgroundColor(const string filledBackgroundColor) {
        this->filledBackgroundColor = filledBackgroundColor;
        render();
        return *this;
    }
    progress_bar
    PBsetFilledForegroundColor(const string filledForegroundColor) {
        this->filledForegroundColor = filledForegroundColor;
        render();
        return *this;
    }
    progress_bar
    PBsetUnfilledBackgroundColor(const string unfilledBackgroundColor) {
        this->unfilledBackgroundColor = unfilledBackgroundColor;
        render();
        return *this;
    }
    progress_bar
    PBsetUnfilledForegroundColor(const string unfilledForegroundColor) {
        this->unfilledForegroundColor = unfilledForegroundColor;
        render();
        return *this;
    }
    progress_bar PBsetX(const float x) {
      this->x = x;
      return *this;
    }
    progress_bar PBsetY(const float y) {
      this->y = y;
      return *this;
    }
    progress_bar PBsetWidth(const float width) {
      this->width = width;
      return *this;
    }
    progress_bar PBsetHeight(const float height) {
      this->height = height;
      return *this;
    }
    progress_bar PBsetBorderSize(const float borderSize) {
      this->borderSize = borderSize;
      return *this;
    }

    float PBgetX() { return x; }
    float PBgetY() { return y; }
    float PBgetWidth() { return width; }
    float PBgetHeight() { return height; }
    float PBgetBorderSize() { return borderSize; }
    float PBgetValue() { return value; }
    float PBgetMaxValue() { return maxValue; }
    float PBgetStep() { return step; }
    char PBgetBackground() { return background; }
    char PBgetFilledBackground() { return filledBackground; }
    char PBgetUnfilledBackground() { return unfilledBackground; }
    string PBgetBackgroundBackgroundColor() { return backgroundBackgroundColor; }
    string PBgetBackgroundForegroundColor() { return backgroundForegroundColor; }
    string PBgetFilledBackgroundColor() { return filledBackgroundColor; }
    string PBgetFilledForegroundColor() { return filledForegroundColor; }
    string PBgetUnfilledBackgroundColor() { return unfilledBackgroundColor; }
    string PBgetUnfilledForegroundColor() { return unfilledForegroundColor; }
};
class container : public Imcurses_widget{
public:
    mcurses_simple_figures *msf;
    void render() override{
        for(int i = 0; i < getAll().size(); i++){
            getAll()[i]->render();
        }
    }
    void show() override{
        isHided = 0;
        for(int i = 0; i < getAll().size(); i++){
          getAll()[i]->show();
        }
    }
    void hide() override{
        isHided = 2;
        for(int i = 0; i < getAll().size(); i++){
          getAll()[i]->hide();
        }
    }
    container(mcurses_simple_figures &msf){
      this->msf = &msf;
    }
    container(const float x, const float y, const float aspect,
                         mcurses_simple_figures &msf, const char background)
        : container(msf) {
      msf.screen->setBackground(background);
    }

    container add(Imcurses_widget* widget){
        mwvector.push_back(widget);
        return *this;
    }

    vector<Imcurses_widget*> getAll(){
        return mwvector;
    }
    container moveX(float x){
        this->x += x;
        for(int i = 0; i < getAll().size(); i++){
            getAll()[i]->x += x;
        }
        return *this;
    }
    container moveY(float y){
        this->y += y;
        for(int i = 0; i < getAll().size(); i++){
          getAll()[i]->y += y;
          getAll()[i]->render();
        }
        return *this;
    }
  private:
    vector<Imcurses_widget*> mwvector;
};
class window : public container{
public:
  static enum shadows{UP_LEFT=0,UP,UP_RIGHT,RIGHT,DOWN_RIGHT,DOWN,DOWN_LEFT,LEFT} shadowTypes;

  mcurses_simple_figures *msf;
  window(mcurses_simple_figures &msf, float x, float y, float width, float height, string backgroundColor, int shadow, int shadowType)
      : window(msf,x,y,width,height,backgroundColor,shadow,shadowType,"BLACK"){}
  window(mcurses_simple_figures &msf, float x, float y, float width, float height, string backgroundColor, int shadow, int shadowType, string shadowColor) : container(msf){
      this->x=x;
      this->y=y;
      this->shadow = shadow;
      this->backgroundColor = backgroundColor;
      this->shadowColor = shadowColor;
      this->width = width;
      this->height = height;
      this->shadowType=shadowType;
      this->msf=&msf;
  }

  void render() override{
    if(shadow != 0){
      switch(shadowType){
      case UP_LEFT:
        msf->drawBorder(x-shadow,y-shadow,width,height-1,shadow,shadowColor);
        break;
      case UP:
        msf->drawBorder(x,y-shadow,width,height-1,shadow,shadowColor);
        break;
      case UP_RIGHT:
        msf->drawBorder(x+1,y-shadow,width+shadow-1,height-1,shadow,shadowColor);
        break;
      case DOWN_LEFT:
        msf->drawBorder(x-shadow,y+shadow,width,height-1,shadow,shadowColor);
        break;
      case DOWN:
        msf->drawBorder(x,y+shadow,width,height-1,shadow,shadowColor);
        break;
      case DOWN_RIGHT:
        msf->drawBorder(x+shadow,y+shadow,width,height-1,shadow,shadowColor);
        break;
      case LEFT:
        msf->drawBorder(x-shadow,y,width,height-1,shadow,shadowColor);
        break;
      case RIGHT:
        msf->drawBorder(x+shadow,y,width,height-1,shadow,shadowColor);
        break;
      }
    }
    msf->drawRectangle(x,y,width,height,backgroundColor);
    for(int i = 0; i < getAll().size(); i++){
      getAll()[i]->render();
    }
  }
  void show() override{
      isHided = 0;
  }
  void hide() override{
      isHided = 2;
  }
private:
  int shadow = 1,
      shadowType;
  float width, height;
  string backgroundColor = "WHITE",
         shadowColor = "BLACK";
};
class label : public Imcurses_widget{
public:
    mcurses_simple_figures* msf;
    label(mcurses_simple_figures &msf,float x, float y,string text){
        this->x = x;
        this->y = y;
        this->msf = &msf;
        this->text = text;
    }
    void render() override{
        msf->print(text,x,y,"RED","WHITE");
    }
    void show() override{
        isHided = 0;
        render();
    }
    void hide() override{
        isHided = 2;
    }
private:
    string text = "";
public:
    float getX(){return x;}
    float getY(){return y;}
    string getText(){return text;}
    label setX(float x){
        this->x = x;
        return *this;
    }
    label setY(float y){
        this->x = x;
        return *this;
    }
    label setText(string text){
        this->text = text;
        return *this;
    }
};
}
