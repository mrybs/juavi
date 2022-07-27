#include "../mcurses_widget.h"
#include "../modules/mcurses_simple_figures.h"
#include <vector>
#define watch(x) cout<<"Var is "<<x;

namespace mcurses {

class progress_bar : public Imcurses_widget{
public:
    mcurses_simple_figures *msf;
    progress_bar(const int x, const int y, const int aspect,
                         const int width, const int height,
                         const int borderSize, mcurses_simple_figures &msf){
      this->x=x;
      this->y=y;
      this->msf = &msf;
      this->width=width;
      this->height=height;
      this->borderSize=borderSize;
      this->aspect=aspect;
    }
    progress_bar(const int x, const int y, const int aspect,
                         mcurses_simple_figures &msf, const std::string background)
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
              ->drawRectangle(x + borderSize, y + borderSize, width, height,
                             unfilledForegroundColor, unfilledBackgroundColor,
                             unfilledBackground)
              ->drawRectangle(x + borderSize, y + borderSize, float(PX), height,
                             filledForegroundColor, filledBackgroundColor,
                             filledBackground);
      }else if(isHided == 2){
            msf->drawRectangle(x, y, width + (borderSize*2), height + borderSize, backgroundForegroundColor, backgroundBackgroundColor);
      }
    }

private:
    char isHided = 1;
    int width = 1,
          height = 1,
          borderSize = 1;
    int value = 0,
        maxValue = 1,
        step = 1;
    std::string background = "-",
         filledBackground = "#",
         unfilledBackground = ".";
    std::string backgroundBackgroundColor = "WHITE",
           backgroundForegroundColor = "BLACK",
           filledBackgroundColor = "GREEN",
           filledForegroundColor = "WHITE",
           unfilledBackgroundColor = "GRAY",
           unfilledForegroundColor = "WHITE";

public:
    progress_bar* PBsetValue(const int value) {
        this->value = value;
        render();
        return this;
    }
    progress_bar* PBsetMaxValue(const int maxValue) {
        this->maxValue = maxValue;
        render();
        return this;
    }
    progress_bar* PBsetStep(const int step) {
        this->step = step;
        render();
        return this;
    }
    progress_bar* PBsetBackground(const std::string background) {
        this->background = background;
        render();
        return this;
    }
    progress_bar* PBsetFilledBackground(const std::string filledBackground) {
        this->filledBackground = filledBackground;
        render();
        return this;
    }
    progress_bar PBsetUnfilledBackground(const std::string unfilledBackground) {
        this->unfilledBackground = unfilledBackground;
        render();
        return *this;
    }
    progress_bar*
    PBsetBackgroundBackgroundColor(const std::string backgroundBackgroundColor) {
        this->backgroundBackgroundColor = backgroundBackgroundColor;
        render();
        return this;
    }
    progress_bar
    PBsetBackgroundForegroundColor(const std::string backgroundForegroundColor) {
        this->backgroundForegroundColor = backgroundForegroundColor;
        render();
        return *this;
    }
    progress_bar*
    PBsetFilledBackgroundColor(const std::string filledBackgroundColor) {
        this->filledBackgroundColor = filledBackgroundColor;
        render();
        return this;
    }
    progress_bar*
    PBsetFilledForegroundColor(const std::string filledForegroundColor) {
        this->filledForegroundColor = filledForegroundColor;
        render();
        return this;
    }
    progress_bar*
    PBsetUnfilledBackgroundColor(const std::string unfilledBackgroundColor) {
        this->unfilledBackgroundColor = unfilledBackgroundColor;
        render();
        return this;
    }
    progress_bar*
    PBsetUnfilledForegroundColor(const std::string unfilledForegroundColor) {
        this->unfilledForegroundColor = unfilledForegroundColor;
        render();
        return this;
    }
    progress_bar* PBsetX(const int x) {
      this->x = x;
      return this;
    }
    progress_bar* PBsetY(const int y) {
      this->y = y;
      return this;
    }
    progress_bar PBsetWidth(const int width) {
      this->width = width;
      return *this;
    }
    progress_bar* PBsetHeight(const int height) {
      this->height = height;
      return this;
    }
    progress_bar* PBsetBorderSize(const int borderSize) {
      this->borderSize = borderSize;
      return this;
    }

    int PBgetX() { return x; }
    int PBgetY() { return y; }
    int PBgetWidth() { return width; }
    int PBgetHeight() { return height; }
    int PBgetBorderSize() { return borderSize; }
    int PBgetValue() { return value; }
    int PBgetMaxValue() { return maxValue; }
    int PBgetStep() { return step; }
    std::string PBgetBackground() { return background; }
    std::string PBgetFilledBackground() { return filledBackground; }
    std::string PBgetUnfilledBackground() { return unfilledBackground; }
    std::string PBgetBackgroundBackgroundColor() { return backgroundBackgroundColor; }
    std::string PBgetBackgroundForegroundColor() { return backgroundForegroundColor; }
    std::string PBgetFilledBackgroundColor() { return filledBackgroundColor; }
    std::string PBgetFilledForegroundColor() { return filledForegroundColor; }
    std::string PBgetUnfilledBackgroundColor() { return unfilledBackgroundColor; }
    std::string PBgetUnfilledForegroundColor() { return unfilledForegroundColor; }
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
    explicit container(mcurses_simple_figures &msf){
      this->msf = &msf;
    }
    container(const float x, const float y, const float aspect,
                         mcurses_simple_figures &msf, const std::string background)
        : container(msf) {
      msf.screen->setBackground(background);
    }

    container* add(Imcurses_widget* widget){
        mwvector.push_back(widget);
        return this;
    }

    std::vector<Imcurses_widget*> getAll(){
        return mwvector;
    }
    container* moveX(float x){
        this->x += x;
        for(int i = 0; i < getAll().size(); i++){
            getAll()[i]->x += x;
        }
        return this;
    }
    container* moveY(float y){
        this->y += y;
        for(int i = 0; i < getAll().size(); i++){
          getAll()[i]->y += y;
          getAll()[i]->render();
        }
        return this;
    }
  private:
      std::vector<Imcurses_widget*> mwvector;
};
class window : public container{
public:
  static enum shadows{UP_LEFT=0,UP,UP_RIGHT,RIGHT,DOWN_RIGHT,DOWN,DOWN_LEFT,LEFT} shadowTypes;

  mcurses_simple_figures *msf;
  window(mcurses_simple_figures &msf, int x, int y, int aspect,int width, int height, std::string backgroundColor, int shadow, int shadowType)
      : window(msf,x,y,aspect,width,height,backgroundColor,shadow,shadowType,"BLACK"){}
  window(mcurses_simple_figures &msf, int x, int y, int aspect,int width, int height, std::string backgroundColor, int shadow, int shadowType, std::string shadowColor) : container(msf){
      this->x=x+1;
      this->y=y;
      this->shadow = shadow;
      this->backgroundColor = backgroundColor;
      this->shadowColor = shadowColor;
      this->width = width;
      this->height = height;
      this->shadowType=shadowType;
      this->msf=&msf;
      this->aspect=aspect;
  }

  void render() override{
      if(shadow != 0){
          switch(shadowType){
          case UP_LEFT:
              msf->drawRectangle(x-shadow,y-shadow,width-1,height-1,shadowColor);
              break;
          case UP:
              msf->drawRectangle(x,y-shadow,width,height-1,shadowColor);
              break;
          case UP_RIGHT:
              msf->drawRectangle(x+shadow,y-shadow,width+shadow-1-1,height-1,shadowColor);
              break;
          case DOWN_LEFT:
              msf->drawRectangle(x-shadow,y+shadow,width-1,height,shadowColor);
              break;
          case DOWN:
              msf->drawRectangle(x,y+shadow,width,height,shadowColor);
              break;
          case DOWN_RIGHT:
              msf->drawRectangle(x+shadow,y+shadow,width,height,shadowColor);
              break;
          case LEFT:
              msf->drawRectangle(x-shadow,y,width,height,shadowColor);
              break;
          case RIGHT:
              msf->drawRectangle(x+shadow,y,width,height,shadowColor);
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
  int width, height;
  std::string backgroundColor = "WHITE",
         shadowColor = "BLACK";
};
class label : public Imcurses_widget{
public:
    mcurses_simple_figures* msf;
    label(mcurses_simple_figures &msf,int x, int y,int aspect,std::string text){
        this->x = x;
        this->y = y;
        this->msf = &msf;
        this->text = text;
        this->aspect=aspect;
    }
    void render() override{
        msf->print(text,x,y,"RED","WHITE");
    }
    void show() override{
        isHided = 0;
    }
    void hide() override{
        isHided = 2;
    }
private:
    std::string text = "";
public:
    std::string getText(){return text;}
    label* setText(std::string text){
        this->text = text;
        return this;
    }
};
class stackedContainer : public Imcurses_widget{
public:
    mcurses_simple_figures *msf;

    void render() override{
        if(getPagesCount() > 0)
            pages[currentPage]->render();
    }
    void show() override{
        isHided = 0;
    }
    void hide() override{
        isHided = 2;
    }

    stackedContainer(mcurses_simple_figures &msf){
        this->msf=&msf;
    }

    std::vector<container*> getPages(){
        return pages;
    }
    int getPagesCount(){
        return pages.size();
    }
    stackedContainer* selectPage(int page){
        if(getPagesCount() <= page) return this;
        currentPage = page;
        render();
        return this;
    }
    stackedContainer* add(container *page){
        pages.push_back(page);
        return this;
    }

private:
    int currentPage = 0;
    std::vector<container*> pages;

};
class tabContainer : public container{
public:
    struct tab{
        container* widgets;
        std::string name;
    };
    mcurses_simple_figures *msf;
    tabContainer(mcurses_simple_figures &msf, int x, int y, int aspect, int width) : container(msf){
        this->x=x;
        this->y=y;
        this->width=width;
        this->msf=&msf;
        this->aspect=aspect;
    }
    void render() override{
        msf->drawLine(x,y,width,false,backgroundForegroundColor,backgroundBackgroundColor);
        int curX = x;
        for(auto i : tabs){
            if(tabs[currentTab] == i)
                print(i->name, curX, y, selectedForegroundColor, selectedBackgroundColor);
            else
                print(i->name, curX, y, unselectedForegroundColor, unselectedBackgroundColor);
            curX += i->name.size()/aspect/aspect+1;
        }
        if(getTabsCount() > 0)
            tabs[currentTab]->widgets->render();
    }
    std::vector<tab*> getTabs(){
        return tabs;
    }
    int getTabsCount(){
        return tabs.size();
    }
    tabContainer* selectTab(int tabID){
        if(getTabsCount() <= tabID) return this;
        currentTab = tabID;
        render();
        return this;
    }
    tabContainer* add(tab *T){
        tabs.push_back(T);
        return this;
    }
private:
  int currentTab = 0;
  int width;
  std::vector<tab*> tabs;
  std::string selectedForegroundColor="BLUE", selectedBackgroundColor="YELLOW",
              unselectedForegroundColor="YELLOW", unselectedBackgroundColor="BLUE",
              backgroundForegroundColor="YELLOW", backgroundBackgroundColor="BLUE";
};
}
