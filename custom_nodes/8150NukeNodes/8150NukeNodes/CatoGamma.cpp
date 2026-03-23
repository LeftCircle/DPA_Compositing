// Add.C
// Copyright (c) 2009 The Foundry Visionmongers Ltd.  All Rights Reserved.

static const char* const HELP = "Adds a constant to a set of channels";

#include "DDImage/PixelIop.h"
#include "DDImage/Row.h"
#include "DDImage/Knobs.h"

using namespace DD::Image;

class CatoGamma : public PixelIop
{
  double value;
public:
  void in_channels(int input, ChannelSet& mask) const;
  CatoGamma(Node* node) : PixelIop(node)
  {
    value = 0;
  }
  bool pass_transform() const { return true; }
  void pixel_engine(const Row &in, int y, int x, int r, ChannelMask, Row & out);
  virtual void knobs(Knob_Callback);
  static const Iop::Description d;
  const char* Class() const { return d.name; }
  const char* node_help() const { return HELP; }
  void _validate(bool);
};

void CatoGamma::_validate(bool for_real)
{
  copy_info();
  //for (unsigned i = 0; i < 4; i++) {
  if (value) {
    set_out_channels(Mask_All);
    info_.black_outside(false);
    return;
  }
  //}
  set_out_channels(Mask_None);
}

void CatoGamma::in_channels(int input, ChannelSet& mask) const
{
  // mask is unchanged
}

void CatoGamma::pixel_engine(const Row& in, int y, int x, int r,
                       ChannelMask channels, Row& out)
{
  const float gamma = 1.0 / value;
  foreach (z, channels) {
    //const float c = value[colourIndex(z)];
    const float* inptr = in[z] + x;
    const float* END = inptr + (r - x);
    float* outptr = out.writable(z) + x;
    while (inptr < END)
      //*outptr++ = *inptr++ + c;
      *outptr++ = pow(*inptr++, gamma);
  }
}

void CatoGamma::knobs(Knob_Callback f)
{
  //AColor_knob(f, value, IRange(0, 4), "value");
  Float_knob(f, &value, "value");
}

#include "DDImage/NukeWrapper.h"

static Iop* build(Node* node) { return new NukeWrapper(new CatoGamma(node)); }
const Iop::Description CatoGamma::d("CatoGamma", "Color/Math/CatoGamma", build);
