#include "ClockLEDMatrixDisplay.h"
#include "CustomFont5x7Fixed.h"  //https://github.com/robjen/GFX_fonts/tree/master/GFX_fonts

ClockLEDMatrixDisplay::ClockLEDMatrixDisplay() {
  mMatrix = NULL;
  mDisplayStringManager = NULL;
  mPeriodScroll = new Period(this, 40, true);
}
ClockLEDMatrixDisplay::~ClockLEDMatrixDisplay() {
}
void ClockLEDMatrixDisplay::Init() {
  // MATRIX DECLARATION:
  // Parameter 1 = width of NeoPixel matrix
  // Parameter 2 = height of matrix
  // Parameter 3 = pin number (most are valid)
  // Parameter 4 = matrix layout flags, add together as needed:
  //   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
  //     Position of the FIRST LED in the matrix; pick two, e.g.
  //     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
  //   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
  //     rows or in vertical columns, respectively; pick one or the other.
  //   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
  //     in the same order, or alternate lines reverse direction; pick one.
  //   See example below for these values in action.
  // Parameter 5 = pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
  //   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
  // Example for NeoPixel Shield.  In this application we'd like to use it
  // as a 5x8 tall matrix, with the USB port positioned at the top of the
  // Arduino.  When held that way, the first pixel is at the top right, and
  // lines are arranged in columns, progressive order.  The shield uses
  // 800 KHz (v2) pixels that expect GRB color data.
  //---------------------------------------------
  mMatrix = new Adafruit_NeoMatrix(8, 8, Cfg.GetMatrixPin(), NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);
  //mMatrix = new Adafruit_NeoMatrix(8, 8, Cfg.GetMatrixPin(), NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);
  mMatrix->begin();
  mFirstColumnBackOffset = mMatrix->width();
  mMatrix->setFont(&CustomFont5x7Fixed);
  mMatrix->setTextWrap(false);
  mMatrix->setBrightness(10);
  mPeriodScroll->AddOnPeriodExpiredHandler(ClockLEDMatrixDisplay::OnPeriodExpiredStaticScroll);
}
void ClockLEDMatrixDisplay::Check() {
  mPeriodScroll->Check(millis());
}
void ClockLEDMatrixDisplay::SetDisplayStringManager(DisplayStringManager* displayStringManager) {
  mDisplayStringManager = displayStringManager;
  mDisplayStringManager->AddOnDisplayStringHandlerChanged(ClockLEDMatrixDisplay::OnDisplayStringHandlerChangedStatic);
}
void ClockLEDMatrixDisplay::OnEndOfScrolling() {
  if (mDisplayStringManager) {
    mDisplayStringManager->SwitchToNext();
  }
}
void ClockLEDMatrixDisplay::OnPeriodExpiredStaticScroll(void* instance) {
  ClockLEDMatrixDisplay* clmd = (ClockLEDMatrixDisplay*)instance;
  if (clmd != NULL) clmd->OnPeriodExpiredScroll();
}
void ClockLEDMatrixDisplay::OnPeriodExpiredScroll() {
  String stringToDisplay = (mDisplayStringManager) ? mDisplayStringManager->GetCurrent()->GetDisplayString() : "";
  //------------------------------------------------------------
  mMatrix->fillScreen(0);
  mMatrix->setCursor(mFirstColumnBackOffset, 7);
  //------------------------------------------------------------
  uint32_t tempColor = strtol(Cfg.GetColor().c_str(), NULL, 16);
  if (tempColor == 0) tempColor = strtol(mDisplayStringManager->GetCurrent()->GetColor().c_str(), NULL, 16);
  uint8_t tempColorR = (tempColor >> 16) & 0xFF;
  uint8_t tempColorG = (tempColor >> 8) & 0xFF;
  uint8_t tempColorB = (tempColor >> 0) & 0xFF;
  mMatrix->setTextColor(mMatrix->Color(tempColorG, tempColorR, tempColorB));
  //------------------------------------------------------------
  mMatrix->print(stringToDisplay);
  //------------------------------------------------------------
  int16_t x = 0, y = 0;  // Text position
  int16_t x1, y1;        // Top-left corner of bounding box
  uint16_t w, h;
  mMatrix->getTextBounds(stringToDisplay, x, y, &x1, &y1, &w, &h);
  //------------------------------------------------------------
  if (--mFirstColumnBackOffset < -w) this->OnEndOfScrolling();
  //------------------------------------------------------------
  mMatrix->show();
}
void ClockLEDMatrixDisplay::OnDisplayStringHandlerChangedStatic(void* instance) {
  ClockLEDMatrixDisplay* clmd = (ClockLEDMatrixDisplay*)instance;
  if (clmd != NULL) clmd->OnDisplayStringHandlerChanged();
}
void ClockLEDMatrixDisplay::OnDisplayStringHandlerChanged() {
  mFirstColumnBackOffset = mMatrix->width();
}