//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   R E G I O N   B A S E D   O B J E C T   D E C T E C T O R   C L A S S   H E A D E R
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef REGIONBASEDOBJECTDETECTOR_H
#define REGIONBASEDOBJECTDETECTOR_H

// System includes

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "opennn.h"

//using namespace opennn;

namespace opennn
{

struct BoundingBox;
struct GroundTruth;
struct Image;

class RegionBasedObjectDetector
{

public:

    // Constructors

    explicit RegionBasedObjectDetector();

    explicit RegionBasedObjectDetector(NeuralNetwork*);

    virtual ~RegionBasedObjectDetector();


    Tensor<BoundingBox, 1> detect_objects(Tensor<Index, 1>&) const;

    BoundingBox get_unique_bounding_box(const Tensor<unsigned char, 1>&,
                                                      const Index&, const Index&,
                                                      const Index&, const Index&) const;

    Tensor<BoundingBox, 1> propose_regions(const Tensor<unsigned char, 1>&) const;

    BoundingBox warp_single_region(const BoundingBox&, const Index&, const Index&) const;

    Tensor<BoundingBox, 1> warp_regions(const Tensor<BoundingBox, 1>&) const;

    Tensor<Index, 2> calculate_region_outputs(const Tensor<BoundingBox, 1>&) const;

    Tensor<BoundingBox, 1> select_strongest(Tensor<BoundingBox, 1>&) const;

    type calculate_intersection_over_union(const BoundingBox&, const BoundingBox&);

    void generate_data_set(const GroundTruth&);
    void perform_training();

private:

    /// Maximum number of inputs in the neural network.

    NeuralNetwork* neural_network_pointer;

    DataSet* data_set_pointer;

    Index regions_number = 2000;

    type confidence_value = 0.2;

    // Utilities

    void resize_image(const Index&, const Index&);

    void segment_image();

};

struct BoundingBox
{
    /// Default constructor.

    explicit BoundingBox();

//    virtual void print() const;

    Tensor<type, 1> data;

    Index x_center;
    Index y_center;
    Index width;
    Index height;

    Index x_top_left;
    Index y_top_left;
    Index x_bottom_right;
    Index y_bottom_right;

    string label; // ????
    Index score; // ????
};

struct Image
{
    explicit Image();

    Tensor<Index, 1> image;
};



struct GroundTruth
{
    explicit GroundTruth();

    virtual void print() const;

    void load(const string& filename);

    Tensor<BoundingBox, 1> objects;
};

}

#endif

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2021 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
