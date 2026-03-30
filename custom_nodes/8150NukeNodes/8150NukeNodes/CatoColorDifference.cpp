// Copyright (c) 2009 The Foundry Visionmongers Ltd.  All Rights Reserved.

static const char* const CLASS = "CatoColorDifference";

static const char* const HELP =
  "Add all the inputs together";

// Standard plug-in include files.

#include "DDImage/Iop.h"
#include "DDImage/NukeWrapper.h"
using namespace DD::Image;
#include "DDImage/Row.h"
#include "DDImage/Tile.h"
#include "DDImage/Knobs.h"

#include <algorithm>

using namespace std;

class CatoColorDifference : public Iop
{
public:
  
  int minimum_inputs() const { return 2; }
  int maximum_inputs() const { return 2; }
  
  //! Constructor. Initialize user controls to their default values.

  CatoColorDifference (Node* node) : Iop (node)
  {
  }

  ~CatoColorDifference () {}
  
  void _validate(bool);
  void _request(int x, int y, int r, int t, ChannelMask channels, int count);
  
  //! This function does all the work.

  void engine ( int y, int x, int r, ChannelMask channels, Row& out );

  //! Return the name of the class.

  const char* Class() const { return CLASS; }
  const char* node_help() const { return HELP; }

  //! Information to the plug-in manager of DDNewImage/Nuke.

  static const Iop::Description description;

}; 


/*! This is a function that creates an instance of the operator, and is
   needed for the Iop::Description to work.
 */
static Iop* CatoColorDifferenceCreate(Node* node)
{
  return new CatoColorDifference(node);
}

/*! The Iop::Description is how NUKE knows what the name of the operator is,
   how to create one, and the menu item to show the user. The menu item may be
   0 if you do not want the operator to be visible.
 */
const Iop::Description CatoColorDifference::description ( CLASS, "Merge/CatoColorDifference",
                                                     CatoColorDifferenceCreate );


void CatoColorDifference::_validate(bool for_real)
{
  copy_info(); // copy bbox channels etc from input0
  merge_info(1); // merge info from input 1
}

void CatoColorDifference::_request(int x, int y, int r, int t, ChannelMask channels, int count)
{
  // request from input 0 and input 1
  input(0)->request( x, y, r, t, channels, count );
  input(1)->request( x, y, r, t, channels, count );
}


/*! For each line in the area passed to request(), this will be called. It must
   calculate the image data for a region at vertical position y, and between
   horizontal positions x and r, and write it to the passed row
   structure. Usually this works by asking the input for data, and modifying
   it.

 */
void CatoColorDifference::engine ( int y, int x, int r,
                              ChannelMask channels, Row& row )
{
    // input 0 row //BACKGROUND
    row.get(input0(), y, x, r, channels);

    // input 1 row // FOREGROUND
    Row input1Row(x, r);
    input1Row.get(input1(), y, x, r, channels);

    // Foreground
    const float* input1_r = input1Row[Chan_Red] + x;
    const float* input1_g = input1Row[Chan_Green] + x;
    const float* input1_b = input1Row[Chan_Blue] + x;

    const float* input0_r = row[Chan_Red] + x;
    const float* input0_g = row[Chan_Green] + x;
    const float* input0_b = row[Chan_Blue] + x;

    float* outptr_b = row.writable(Chan_Blue) + x;
    float* outptr_r = row.writable(Chan_Red) + x;
    float* outptr_g = row.writable(Chan_Green) + x;
    
    float* out_alpha = row.writable(Chan_Alpha) + x;
    const float* end = outptr_b + (r - x);

    float matte;
    while (outptr_b < end) {
        // Basic spill supression
        float spill_suppress_foreground_b = std::min(*input1_g, *input1_b);
        
        matte = 1.0 - std::max(*input1_b - std::max(*input1_r, *input1_g), 0.0f);
        
        *outptr_r = matte * *input0_r + *input1_r;
        *outptr_g = matte * *input0_g + *input1_g;
        *outptr_b = matte * *input0_b + spill_suppress_foreground_b;


        input1_r++; input1_g++; input1_b++;
        input0_r++; input0_g++; input0_b++;
        outptr_b++; out_alpha++; outptr_g++; outptr_r++;
    }
  //}
}
