// A very basic implementation of contrast

static const char* const HELP = "Adds a constant to a set of channels";

#include "DDImage/PixelIop.h"
#include "DDImage/Row.h"
#include "DDImage/Knobs.h"

using namespace DD::Image;

class CatoContrast : public PixelIop
{
  double mult = 3.0;
  double subtract = 0.3;

public:
  void in_channels(int input, ChannelSet& mask) const;
  CatoContrast(Node* node) : PixelIop(node) {}
  
  bool pass_transform() const { return true; }
  void pixel_engine(const Row &in, int y, int x, int r, ChannelMask, Row & out);
  virtual void knobs(Knob_Callback);
  static const Iop::Description d;
  const char* Class() const { return d.name; }
  const char* node_help() const { return HELP; }
  void _validate(bool);
};

void CatoContrast::_validate(bool for_real)
{
  copy_info();
  if (mult) {
    set_out_channels(Mask_All);
    info_.black_outside(false);
    return;
  }
  //}
  set_out_channels(Mask_None);
}

void CatoContrast::in_channels(int input, ChannelSet& mask) const
{
  // mask is unchanged
}

void CatoContrast::pixel_engine(const Row& in, int y, int x, int r,
                       ChannelMask channels, Row& out)
{
  foreach (z, channels) {
    const float* inptr = in[z] + x;
    const float* END = inptr + (r - x);
    float* outptr = out.writable(z) + x;
    while (inptr < END)
      *outptr++ = mult * *inptr++ - subtract;
  }
}

void CatoContrast::knobs(Knob_Callback f)
{
  Float_knob(f, &mult, "multiply");
  Float_knob(f, &subtract, "subtract");
}

#include "DDImage/NukeWrapper.h"

static Iop* build(Node* node) { return new NukeWrapper(new CatoContrast(node)); }
const Iop::Description CatoContrast::d("CatoContrast", "Color/Math/CatoContrast", build);
