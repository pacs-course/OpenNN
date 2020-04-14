//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   N E U R A L   N E T W O R K   T E S T   C L A S S                     
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "neural_network_test.h"

NeuralNetworkTest::NeuralNetworkTest() : UnitTesting()
{
}


NeuralNetworkTest::~NeuralNetworkTest()
{
}


void NeuralNetworkTest::test_constructor()
{
   cout << "test_constructor\n";

  // Test 0 / Default constructor

  NeuralNetwork neural_network_0;

  assert_true(neural_network_0.is_empty(), LOG);
  assert_true(neural_network_0.get_layers_number() == 0, LOG);

  // Test 1 / Model type constructor

  Tensor<Index, 1> architecture(3);

  architecture.setValues({1,4,2});

  NeuralNetwork neural_network_1_1(NeuralNetwork::Approximation, architecture); //CC -> architecture = {inp_n, hddn_neurns_n, out_n}

  assert_true(neural_network_1_1.get_layers_number() == 5, LOG);
  assert_true(neural_network_1_1.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);
  assert_true(neural_network_1_1.get_layer_pointer(1)->get_type() == Layer::Perceptron, LOG);
  assert_true(neural_network_1_1.get_layer_pointer(2)->get_type() == Layer::Perceptron, LOG);
  assert_true(neural_network_1_1.get_layer_pointer(3)->get_type() == Layer::Unscaling, LOG);
  assert_true(neural_network_1_1.get_layer_pointer(4)->get_type() == Layer::Bounding, LOG);

  NeuralNetwork neural_network_1_2(NeuralNetwork::Classification, architecture);

  assert_true(neural_network_1_2.get_layers_number() == 3, LOG);
  assert_true(neural_network_1_2.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);
  assert_true(neural_network_1_2.get_layer_pointer(1)->get_type() == Layer::Perceptron, LOG);
  assert_true(neural_network_1_2.get_layer_pointer(2)->get_type() == Layer::Probabilistic, LOG);

  NeuralNetwork neural_network_1_3(NeuralNetwork::Forecasting, architecture);

  assert_true(neural_network_1_3.get_layers_number() == 4, LOG);
  assert_true(neural_network_1_3.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);
  assert_true(neural_network_1_3.get_layer_pointer(1)->get_type() == Layer::LongShortTermMemory, LOG);
  assert_true(neural_network_1_3.get_layer_pointer(2)->get_type() == Layer::Perceptron, LOG);
  assert_true(neural_network_1_3.get_layer_pointer(3)->get_type() == Layer::Unscaling, LOG);

  NeuralNetwork neural_network_1_4(NeuralNetwork::ImageApproximation, architecture);

  assert_true(neural_network_1_4.get_layers_number() == 1, LOG);
  assert_true(neural_network_1_4.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);

  NeuralNetwork neural_network_1_5(NeuralNetwork::ImageClassification, architecture);

  assert_true(neural_network_1_5.get_layers_number() == 1, LOG);
  assert_true(neural_network_1_5.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);

  // Test 2 / Convolutional layer constructor
/*
  Tensor<Index, 1> new_inputs_dimensions(1);
  new_inputs_dimensions.setConstant(1);

  Index new_blocks_number = 1;

  Tensor<Index, 1> new_filters_dimensions(1);
  new_filters_dimensions.setConstant(1);

  Index new_outputs_number = 1;

  ConvolutionalLayer convolutional_layer(1,1); //CC -> cl(inputs_dim, filters_dim)

  NeuralNetwork neural_network_2(new_inputs_dimensions, new_blocks_number, new_filters_dimensions, new_outputs_number);

  assert_true(neural_network_2.is_empty(), LOG);
  assert_true(neural_network_2.get_layers_number() == 0, LOG);
*/

  // Test 3_1 / Layers constructor //CCH -> Test other type of layers

  Tensor<Layer*, 1> layers_2;

  NeuralNetwork neural_network_3_1(layers_2);

  assert_true(neural_network_3_1.is_empty(), LOG);
  assert_true(neural_network_3_1.get_layers_number() == 0, LOG);

  PerceptronLayer* perceptron_layer_3_1 = new PerceptronLayer(1, 1);   //CC -> PerceptronLayer(inputs_numb, neurons_numb)

  neural_network_3_1.add_layer(perceptron_layer_3_1);

  assert_true(!neural_network_3_1.is_empty(), LOG);
  assert_true(neural_network_3_1.get_layer_pointer(0)->get_type() == Layer::Perceptron, LOG);

  // Test 3_2

  PerceptronLayer* perceptron_layer_3_2 = new PerceptronLayer(1, 1);

  Tensor<Layer*, 1> layers_3(1);     //CC -> {l1, l2, ... , ln} --- i.e {pl, pbl, sl}

  layers_3(0) = perceptron_layer_3_2;

  NeuralNetwork neural_network_3_2(layers_3);

  assert_true(!neural_network_3_2.is_empty(), LOG);
  assert_true(neural_network_3_2.get_layers_number() == 1, LOG);
  assert_true(neural_network_3_2.get_layer_pointer(0)->get_type() == Layer::Perceptron, LOG);

  // Copy constructor

/*
  NeuralNetwork neural_network_4(neural_network_1_1);
  assert_true(neural_network_4.get_layers_number() == 5, LOG);
*/

   // File constructor

//   neural_network.save(file_name);
//   NeuralNetwork nn6(file_name);

}

void NeuralNetworkTest::test_destructor()
{
   cout << "test_destructor\n";

   NeuralNetwork* neural_network_1 = new NeuralNetwork;

   delete neural_network_1;
}



void NeuralNetworkTest::test_assignment_operator()
{
   cout << "test_assignment_operator\n";

   NeuralNetwork nn1;
   NeuralNetwork nn2 = nn1;
}

void NeuralNetworkTest::test_get_display()
{
   cout << "test_get_display\n";
}

// APPENDING LAYERS

void NeuralNetworkTest::test_add_layer()
{
   cout << "test_add_layer\n";

   NeuralNetwork neural_network_;

   LongShortTermMemoryLayer* long_short_term_memory_layer = new LongShortTermMemoryLayer;
   neural_network_.add_layer(long_short_term_memory_layer);
   assert_true(neural_network_.get_layers_number() == 1, LOG);
   assert_true(neural_network_.get_layer_pointer(0)->get_type() == Layer::LongShortTermMemory, LOG);

   NeuralNetwork neural_network__;

   RecurrentLayer* recurrent_layer = new RecurrentLayer;
   neural_network__.add_layer(recurrent_layer);
   assert_true(neural_network__.get_layers_number() == 1, LOG);
   assert_true(neural_network__.get_layer_pointer(0)->get_type() == Layer::Recurrent, LOG);

   NeuralNetwork neural_network;

   ScalingLayer* scaling_layer = new ScalingLayer(1);
   neural_network.add_layer(scaling_layer);
   assert_true(neural_network.get_layers_number() == 1, LOG);
   assert_true(neural_network.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);

   ConvolutionalLayer* convolutional_layer = new ConvolutionalLayer;
   neural_network.add_layer(convolutional_layer);
   assert_true(neural_network.get_layers_number() == 2, LOG);
   assert_true(neural_network.get_layer_pointer(1)->get_type() == Layer::Convolutional, LOG);

   PerceptronLayer* perceptron_layer = new PerceptronLayer;
   neural_network.add_layer(perceptron_layer);
   assert_true(neural_network.get_layers_number() == 3, LOG);
   assert_true(neural_network.get_layer_pointer(2)->get_type() == Layer::Perceptron, LOG);

   PoolingLayer* pooling_layer = new PoolingLayer;

   neural_network.add_layer(pooling_layer);
   assert_true(neural_network.get_layers_number() == 4, LOG);
   assert_true(neural_network.get_layer_pointer(3)->get_type() == Layer::Pooling, LOG);

   ProbabilisticLayer* probabilistic_layer = new ProbabilisticLayer;

   neural_network.add_layer(probabilistic_layer);
   assert_true(neural_network.get_layers_number() == 5, LOG);
   assert_true(neural_network.get_layer_pointer(4)->get_type() == Layer::Probabilistic, LOG);

   UnscalingLayer* unscaling_layer = new UnscalingLayer;

   neural_network.add_layer(unscaling_layer);
   assert_true(neural_network.get_layers_number() == 6, LOG);
   assert_true(neural_network.get_layer_pointer(5)->get_type() == Layer::Unscaling, LOG);

   BoundingLayer* bounding_layer = new BoundingLayer;

   neural_network.add_layer(bounding_layer);
   assert_true(neural_network.get_layers_number() == 7, LOG);
   assert_true(neural_network.get_layer_pointer(6)->get_type() == Layer::Bounding, LOG);

   PrincipalComponentsLayer* principal_components_layer = new PrincipalComponentsLayer;

   neural_network.add_layer(principal_components_layer);
   assert_true(neural_network.get_layers_number() == 8, LOG);
   assert_true(neural_network.get_layer_pointer(7)->get_type() == Layer::PrincipalComponents, LOG);
}

void NeuralNetworkTest::check_layer_type()
{
   cout << "check_layer_type\n";

   // Test 1

   Tensor<Layer*, 1> layers_tensor(2);
   layers_tensor.setValues({new PerceptronLayer, new PerceptronLayer});

   NeuralNetwork neural_network(layers_tensor);

   assert_true(!neural_network.check_layer_type(Layer::LongShortTermMemory), LOG);
   assert_true(!neural_network.check_layer_type(Layer::Recurrent), LOG);

   assert_true(neural_network.check_layer_type(Layer::Scaling), LOG);
   assert_true(neural_network.check_layer_type(Layer::Convolutional), LOG);
   assert_true(neural_network.check_layer_type(Layer::Perceptron), LOG);
   assert_true(neural_network.check_layer_type(Layer::Pooling), LOG);
   assert_true(neural_network.check_layer_type(Layer::Probabilistic), LOG);
   assert_true(neural_network.check_layer_type(Layer::Unscaling), LOG);
   assert_true(neural_network.check_layer_type(Layer::Bounding), LOG);
   assert_true(neural_network.check_layer_type(Layer::PrincipalComponents), LOG);

   // Test 2

   Tensor<Layer*, 1> layers_tensor_1(1);
   layers_tensor_1.setValues({new PerceptronLayer});

   NeuralNetwork neural_network_1(layers_tensor_1);

   assert_true(!neural_network_1.check_layer_type(Layer::LongShortTermMemory), LOG);
   assert_true(!neural_network_1.check_layer_type(Layer::Recurrent), LOG);

   // Test 3

   Tensor<Layer*, 1> layers_tensor_2(1);
   layers_tensor_2.setValues({new ScalingLayer});

   NeuralNetwork neural_network_2(layers_tensor_2);

   assert_true(neural_network_2.check_layer_type(Layer::LongShortTermMemory), LOG);
   assert_true(neural_network_2.check_layer_type(Layer::Recurrent), LOG);
}

// Get methods

void NeuralNetworkTest::test_has_methods()
{
   cout << "test_had_methods\n";

   // Test 0

   Tensor<Layer*, 1> layer_tensor;

   NeuralNetwork neural_network(layer_tensor);

   assert_true(!neural_network.has_scaling_layer(), LOG);
   assert_true(!neural_network.has_principal_components_layer(), LOG);
   assert_true(!neural_network.has_long_short_term_memory_layer(), LOG);
   assert_true(!neural_network.has_recurrent_layer(), LOG);
   assert_true(!neural_network.has_unscaling_layer(), LOG);
   assert_true(!neural_network.has_bounding_layer(), LOG);
   assert_true(!neural_network.has_probabilistic_layer(), LOG);

   // Test 1

   Tensor<Layer*, 1> layer_tensor_1(7);
   layer_tensor_1.setValues({new ScalingLayer, new PrincipalComponentsLayer, new LongShortTermMemoryLayer,
                             new RecurrentLayer, new UnscalingLayer, new BoundingLayer, new ProbabilisticLayer});

   NeuralNetwork neural_network_1(layer_tensor_1);

   assert_true(neural_network_1.has_scaling_layer(), LOG);
   assert_true(neural_network_1.has_principal_components_layer(), LOG);
   assert_true(neural_network_1.has_long_short_term_memory_layer(), LOG);
   assert_true(neural_network_1.has_recurrent_layer(), LOG);
   assert_true(neural_network_1.has_unscaling_layer(), LOG);
   assert_true(neural_network_1.has_bounding_layer(), LOG);
   assert_true(neural_network_1.has_probabilistic_layer(), LOG);
}

void NeuralNetworkTest::test_get_inputs()
{
   cout << "test_get_inputs\n";

   NeuralNetwork neural_network;

   Tensor<string, 1> inputs_names(2);
   inputs_names.setValues({"in_1","in_2"});

   neural_network.set_inputs_names(inputs_names);
   assert_true(neural_network.get_inputs_names().size() == 2, LOG);
   assert_true(neural_network.get_input_name(0) == "in_1", LOG);
   assert_true(neural_network.get_input_name(1) == "in_2", LOG);
   assert_true(neural_network.get_input_index("in_1") == 0, LOG);
   assert_true(neural_network.get_input_index("in_2") == 1, LOG);
}

void NeuralNetworkTest::test_get_outputs()
{
   cout << "test_get_outputs\n";

   NeuralNetwork neural_network;

   Tensor<string, 1> outputs_names(2);
   outputs_names.setValues({"out_1","out_2"});

   neural_network.set_outputs_names(outputs_names);
   assert_true(neural_network.get_outputs_names().size() == 2, LOG);
   assert_true(neural_network.get_output_name(0) == "out_1", LOG);
   assert_true(neural_network.get_output_name(1) == "out_2", LOG);
   assert_true(neural_network.get_output_index("out_1") == 0, LOG);
   assert_true(neural_network.get_output_index("out_2") == 1, LOG);
}

void NeuralNetworkTest::test_get_trainable_layers()
{
   cout << "test_get_trainable_layers\n";

   Tensor<Layer*, 1> layer_tensor(10);
   layer_tensor.setValues({new ScalingLayer, new ConvolutionalLayer, new PerceptronLayer,
                           new PoolingLayer, new ProbabilisticLayer, new LongShortTermMemoryLayer,
                           new RecurrentLayer, new UnscalingLayer, new BoundingLayer, new PrincipalComponentsLayer});

   NeuralNetwork neural_network(layer_tensor);

   assert_true(neural_network.get_trainable_layers_pointers()(0)->get_type() == Layer::Convolutional, LOG);
   assert_true(neural_network.get_trainable_layers_pointers()(1)->get_type() == Layer::Perceptron, LOG);
   assert_true(neural_network.get_trainable_layers_pointers()(2)->get_type() == Layer::Pooling, LOG);
   assert_true(neural_network.get_trainable_layers_pointers()(3)->get_type() == Layer::Probabilistic, LOG);
   assert_true(neural_network.get_trainable_layers_pointers()(4)->get_type() == Layer::LongShortTermMemory, LOG);
   assert_true(neural_network.get_trainable_layers_pointers()(5)->get_type() == Layer::Recurrent, LOG);
   assert_true(neural_network.get_trainable_layers_pointers()(6)->get_type() == Layer::PrincipalComponents, LOG);

   assert_true(neural_network.get_trainable_layers_indices()(0) == 1, LOG);
   assert_true(neural_network.get_trainable_layers_indices()(1) == 2, LOG);
   assert_true(neural_network.get_trainable_layers_indices()(2) == 3, LOG);
   assert_true(neural_network.get_trainable_layers_indices()(3) == 4, LOG);
   assert_true(neural_network.get_trainable_layers_indices()(4) == 5, LOG);
   assert_true(neural_network.get_trainable_layers_indices()(5) == 6, LOG);
   assert_true(neural_network.get_trainable_layers_indices()(6) == 8, LOG);
}

void NeuralNetworkTest::test_get_layers_type_pointers()
{
   cout << "test_get_layers_type_pointers\n";

   // Test 1

   Tensor<Layer*, 1> layer_tensor(10);
   layer_tensor.setValues({new ScalingLayer, new ConvolutionalLayer, new PerceptronLayer,
                           new PoolingLayer, new ProbabilisticLayer, new LongShortTermMemoryLayer,
                           new RecurrentLayer, new UnscalingLayer, new BoundingLayer, new PrincipalComponentsLayer});

   NeuralNetwork neural_network(layer_tensor);

   assert_true(neural_network.get_scaling_layer_pointer()->get_type() == Layer::Scaling, LOG);
   assert_true(neural_network.get_unscaling_layer_pointer()->get_type() == Layer::Unscaling, LOG);
   assert_true(neural_network.get_bounding_layer_pointer()->get_type() == Layer::Bounding, LOG);
   assert_true(neural_network.get_probabilistic_layer_pointer()->get_type() == Layer::Probabilistic, LOG);/*
   assert_true(neural_network.get_principal_components_layer_pointer()->get_type() == Layer::PrincipalComponents, LOG);*/ //CCH
   assert_true(neural_network.get_long_short_term_memory_layer_pointer()->get_type() == Layer::LongShortTermMemory, LOG);
   assert_true(neural_network.get_recurrent_layer_pointer()->get_type() == Layer::Recurrent, LOG);

   assert_true(neural_network.get_first_perceptron_layer_pointer()->get_type() == Layer::Perceptron, LOG);
}

void NeuralNetworkTest::test_get_layer_pointer()
{
   cout << "test_get_layer_pointer\n";

   Tensor<Layer*, 1> layer_tensor(10);
   layer_tensor.setValues({new ScalingLayer, new ConvolutionalLayer, new PerceptronLayer,
                           new PoolingLayer, new ProbabilisticLayer, new LongShortTermMemoryLayer,
                           new RecurrentLayer, new UnscalingLayer, new PrincipalComponentsLayer, new BoundingLayer});

   NeuralNetwork neural_network(layer_tensor);

   assert_true(neural_network.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);
   assert_true(neural_network.get_layer_pointer(1)->get_type() == Layer::Convolutional, LOG);
   assert_true(neural_network.get_layer_pointer(2)->get_type() == Layer::Perceptron, LOG);
   assert_true(neural_network.get_layer_pointer(3)->get_type() == Layer::Pooling, LOG);
   assert_true(neural_network.get_layer_pointer(4)->get_type() == Layer::Probabilistic, LOG);
   assert_true(neural_network.get_layer_pointer(5)->get_type() == Layer::LongShortTermMemory, LOG);
   assert_true(neural_network.get_layer_pointer(6)->get_type() == Layer::Recurrent, LOG);
   assert_true(neural_network.get_layer_pointer(7)->get_type() == Layer::Unscaling, LOG);
   assert_true(neural_network.get_layer_pointer(8)->get_type() == Layer::PrincipalComponents, LOG);
   assert_true(neural_network.get_layer_pointer(9)->get_type() == Layer::Bounding, LOG);

   assert_true(neural_network.get_output_layer_pointer()->get_type() == Layer::Bounding, LOG);
}

// Set methods

void NeuralNetworkTest::test_set()
{
   cout << "test_set\n";

   NeuralNetwork neural_network;

   // Test 0

   neural_network.set();

   assert_true(neural_network.get_inputs_names().size() == 0, LOG);
   assert_true(neural_network.get_outputs_names().size() == 0, LOG);
   assert_true(neural_network.get_layers_pointers().size() == 0, LOG);

   // Test 1

   Tensor<Index, 1> architecture(3);

   architecture.setValues({1,0,1}); //CC -> architecture = {inp_n, hddn_neurns_n, out_n}

   neural_network.set(NeuralNetwork::Approximation, architecture);
   assert_true(neural_network.get_inputs_names().size() == 1, LOG);  //CC -> architecture(0)
   assert_true(neural_network.get_outputs_names().size() == 1, LOG);  //CC -> architecture(architecture.size()-1)
   assert_true(neural_network.get_layers_pointers().size() == 5, LOG);

   neural_network.set(NeuralNetwork::Classification, architecture);
   assert_true(neural_network.get_inputs_names().size() == 1, LOG);  //CC -> architecture(0)
   assert_true(neural_network.get_outputs_names().size() == 1, LOG);  //CC -> architecture(architecture.size()-1)
   assert_true(neural_network.get_layers_pointers().size() == 3, LOG);

   neural_network.set(NeuralNetwork::Forecasting, architecture);
   assert_true(neural_network.get_inputs_names().size() == 1, LOG);  //CC -> architecture(0)
   assert_true(neural_network.get_outputs_names().size() == 1, LOG);  //CC -> architecture(architecture.size()-1)
   assert_true(neural_network.get_layers_pointers().size() == 4, LOG);

   neural_network.set(NeuralNetwork::ImageApproximation, architecture);
   assert_true(neural_network.get_inputs_names().size() == 1, LOG);  //CC -> architecture(0)
   assert_true(neural_network.get_outputs_names().size() == 1, LOG);  //CC -> architecture(architecture.size()-1)
   assert_true(neural_network.get_layers_pointers().size() == 1, LOG);

   neural_network.set(NeuralNetwork::ImageClassification, architecture);
   assert_true(neural_network.get_inputs_names().size() == 1, LOG);  //CC -> architecture(0)
   assert_true(neural_network.get_outputs_names().size() == 1, LOG);  //CC -> architecture(architecture.size()-1)
   assert_true(neural_network.get_layers_pointers().size() == 1, LOG);

   // Test 2 / Convolutional layer set
   /*
   Tensor<Index, 1> new_inputs_dimensions(1);
   new_inputs_dimensions.setConstant(1);

   Index new_blocks_number = 1;

   Tensor<Index, 1> new_filters_dimensions(1);
   new_filters_dimensions.setConstant(1);

   Index new_outputs_number = 1;

   ConvolutionalLayer convolutional_layer(1,1); //CC -> cl(inputs_dim, filters_dim)

   neural_network.set(new_inputs_dimensions, new_blocks_number, new_filters_dimensions, new_outputs_number);

   assert_true(neural_network.is_empty(), LOG);
   assert_true(neural_network.get_layers_number() == 0, LOG);
   */

   // Test 3 / Copy layer set
/*
   NeuralNetwork neural_network_3_0;
   NeuralNetwork neural_network_3_1;

   Tensor<Index, 1> architecture_3_0(3);
   architecture_3_0.setValues({1,0,1});

   Tensor<Index, 1> architecture_3_1(3);
   architecture_3_1.setValues({5,0,5});

   neural_network_3_0.set(NeuralNetwork::Approximation, architecture_3_0);
   neural_network_3_1.set(NeuralNetwork::Approximation, architecture_3_1);

   neural_network_3_1.set(neural_network_3_0);

   assert_true(neural_network_3_1.get_inputs_names().size() == 1, LOG);  //CC -> architecture(0)
   assert_true(neural_network_3_1.get_outputs_names().size() == 1, LOG);  //CC -> architecture(architecture.size()-1)
   assert_true(neural_network_3_1.get_layers_pointers().size() == 1, LOG);
   */
}

void NeuralNetworkTest::test_set_names()
{
   cout << "test_set_names\n";

   NeuralNetwork neural_network;

   // Test 0

   Tensor<string, 1> inputs_names;
   Tensor<string, 1> outputs_names;

   neural_network.set_inputs_names(inputs_names);
   neural_network.set_outputs_names(outputs_names);
   assert_true(neural_network.get_inputs_names().size() == 0, LOG);
   assert_true(neural_network.get_outputs_names().size() == 0, LOG);

   // Test 1

   Tensor<string, 1> inputs_names_1(2);
   inputs_names_1.setValues({"in_1","in_2"});
   Tensor<string, 1> outputs_names_1(2);
   outputs_names_1.setValues({"out_1","out_2"});

   neural_network.set_inputs_names(inputs_names_1);
   neural_network.set_outputs_names(outputs_names_1);
   assert_true(neural_network.get_inputs_names().size() == 2, LOG);
   assert_true(neural_network.get_inputs_names()(0) == "in_1", LOG);
   assert_true(neural_network.get_inputs_names()(1) == "in_2", LOG);
   assert_true(neural_network.get_outputs_names().size() == 2, LOG);
   assert_true(neural_network.get_outputs_names()(0) == "out_1", LOG);
   assert_true(neural_network.get_outputs_names()(1) == "out_2", LOG);
}

void NeuralNetworkTest::test_set_number()
{
   cout << "test_set_number\n";

   Tensor<Index, 1> architecture(3);
   architecture.setValues({1,0,1});

   NeuralNetwork neural_network(NeuralNetwork::Classification, architecture);

   // Test 0_0

   Index inputs_number;
   neural_network.set_inputs_number(inputs_number);

   assert_true(neural_network.get_inputs_number() == 0, LOG);
   assert_true(neural_network.get_layer_pointer(0)->get_inputs_number() == 0, LOG); //CC -> Scaling layer nmb assert

   // Test 0_1

   inputs_number = 3;

   neural_network.set_inputs_number(inputs_number);
   assert_true(neural_network.get_inputs_number() == 3, LOG);
   assert_true(neural_network.get_layer_pointer(0)->get_inputs_number() == 3, LOG); //CC -> Scaling layer nmb assert

   // Test 1_0
/*
   Tensor<bool, 1> inputs_names_1;
   neural_network.set_inputs_number(inputs_names_1);

   assert_true(neural_network.get_inputs_number() == 0, LOG);
*/

   // Test 1_1

   Tensor<bool, 1> inputs_names_1_1(2);
   inputs_names_1_1.setValues({true,false});

   neural_network.set_inputs_number(inputs_names_1_1);
   assert_true(neural_network.get_inputs_number() == 1, LOG);
}

void NeuralNetworkTest::test_set_default()
{
   cout << "test_set_default\n";

   NeuralNetwork neural_network;

   neural_network.set_default();

   assert_true(display == true, LOG);
}

void NeuralNetworkTest::test_set_pointers()
{
   cout << "test_set_pointers\n";

   Tensor<Index, 1> architecture(3);
   architecture.setValues({1,0,1});

   NeuralNetwork neural_network(NeuralNetwork::Classification, architecture);

   // Test 1 // Device

   Device device(Device::EigenThreadPool);
   neural_network.set_device_pointer(&device);

   assert_true(neural_network.get_layers_number() == 3, LOG);
   assert_true(device.get_type() == Device::EigenThreadPool, LOG);
//   assert_true(neural_network.get_layer_pointer(0)->device_pointer->get_type() == Device::EigenThreadPool, LOG);
   //CCH -> Need get_device_pointer method?

   // Test 2 // Layers

   NeuralNetwork neural_network_2;

   Tensor<Layer*, 1> layers_tensor(3);
   layers_tensor.setValues({new ScalingLayer(1),new PerceptronLayer(1, 1), new UnscalingLayer(1)});

   neural_network_2.set_layers_pointers(layers_tensor);

   assert_true(!neural_network_2.is_empty(), LOG);
   assert_true(neural_network_2.get_layers_number() == 3, LOG);
   assert_true(neural_network_2.get_layer_pointer(0)->get_type() == Layer::Scaling, LOG);
   assert_true(neural_network_2.get_layer_pointer(1)->get_type() == Layer::Perceptron, LOG);
   assert_true(neural_network_2.get_layer_pointer(2)->get_type() == Layer::Unscaling, LOG);
}

void NeuralNetworkTest::test_set_display()
{
   cout << "test_set_display\n";

   NeuralNetwork neural_network;

   neural_network.set_display(true);
   assert_true(neural_network.get_display() == true, LOG);

   neural_network.set_display(false);
   assert_true(neural_network.get_display() == false, LOG);
}

// Layers

void NeuralNetworkTest::test_get_layers_number()
{
   cout << "test_get_layers_number\n";

   // Test 0

   Tensor<Layer*, 1> layers_tensor;

   NeuralNetwork neural_network(layers_tensor);

   assert_true(neural_network.get_layers_number() == 0, LOG);
   assert_true(neural_network.get_trainable_layers_number() == 0, LOG);
   assert_true(neural_network.get_perceptron_layers_number() == 0, LOG);
   assert_true(neural_network.get_probabilistic_layers_number() == 0, LOG);
//   assert_true(neural_network.get_layers_neurons_numbers()(0) == 0, LOG); //CCH

   // Test 1

   Tensor<Layer*, 1> layers_tensor_1(10);

   layers_tensor_1.setValues({new ScalingLayer, new ConvolutionalLayer, new PerceptronLayer,
                           new PoolingLayer, new ProbabilisticLayer, new LongShortTermMemoryLayer,
                           new RecurrentLayer, new UnscalingLayer, new PrincipalComponentsLayer, new BoundingLayer});

   NeuralNetwork neural_network_1(layers_tensor_1);

   assert_true(neural_network_1.get_layers_number() == 10, LOG);
   assert_true(neural_network_1.get_trainable_layers_number() == 7, LOG);
   assert_true(neural_network_1.get_perceptron_layers_number() == 1, LOG); //CCH
   assert_true(neural_network_1.get_probabilistic_layers_number() == 1, LOG);
//   assert_true(neural_network.get_layers_neurons_numbers()(0) == 0, LOG); //CCH
}

// Architecture

void NeuralNetworkTest::test_inputs_outputs_number()
{
   cout << "test_inputs_outputs_number\n";

   NeuralNetwork neural_network;

   neural_network.set_display(true);
   assert_true(neural_network.get_display() == true, LOG);

   neural_network.set_display(false);
   assert_true(neural_network.get_display() == false, LOG);
}

void NeuralNetworkTest::test_get_architecture()
{
   cout << "test_get_architecture\n";

   NeuralNetwork neural_network;

   neural_network.set_display(true);
   assert_true(neural_network.get_display() == true, LOG);

   neural_network.set_display(false);
   assert_true(neural_network.get_display() == false, LOG);
}





void NeuralNetworkTest::test_set_display_inputs_warning()
{
   cout << "test_set_display_inputs_warning\n";
}



void NeuralNetworkTest::test_get_parameters_number()
{
   cout << "test_get_parameters_number\n";

   NeuralNetwork neural_network;

   // Test

   neural_network.set();
   assert_true(neural_network.get_parameters_number() == 0, LOG);

   // Test

   Tensor<Index, 1> architecture(3);

   architecture.setValues({1,1,1});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   assert_true(neural_network.get_parameters_number() == 4, LOG);
}


void NeuralNetworkTest::test_get_parameters()   
{
   cout << "test_get_parameters\n";

   NeuralNetwork neural_network;
   Tensor<type, 1> parameters;

   // Test

   neural_network.set();
   parameters = neural_network.get_parameters();

   assert_true(parameters.size() == 0, LOG);

   // Test

   Tensor<Index, 1> architecture(3);

   architecture.setValues({1,2,1});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);
   parameters = neural_network.get_parameters();

   assert_true(parameters.size() == 7, LOG);
//   assert_true(parameters == 0.0, LOG);

   // Test

   architecture.resize(4);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);
   parameters = neural_network.get_parameters();

   assert_true(parameters.size() == 6, LOG);
//   assert_true(parameters == 0.0, LOG);
}

void NeuralNetworkTest::test_get_trainable_layers_parameters()
{
    NeuralNetwork neural_network;

    Tensor<Index, 1> architecture(3);

    architecture.setValues({1, 2, 3});

    neural_network.set(NeuralNetwork::Approximation, architecture);

    PerceptronLayer* pl0 = dynamic_cast<PerceptronLayer*>(neural_network.get_layer_pointer(1));

    pl0->set_biases_constant(1);

    pl0->set_synaptic_weights_constant(0);

    PerceptronLayer* pl1 = dynamic_cast<PerceptronLayer*>(neural_network.get_layer_pointer(2));

    pl1->set_biases_constant(3);

    pl1->set_synaptic_weights_constant(2);

    Tensor<type, 1> parameters = neural_network.get_parameters();

    Tensor<Tensor<type, 1>, 1> training_parameters = neural_network.get_trainable_layers_parameters(parameters);

    assert_true(training_parameters(0).size() == 4, LOG);
    assert_true(training_parameters(1).size() == 9, LOG);
    assert_true(training_parameters(0)(0) == 0, LOG);
    assert_true(training_parameters(0)(2) == 1, LOG);
    assert_true(training_parameters(1)(0) == 2, LOG);
    assert_true(training_parameters(1)(6) == 3, LOG);

}


void NeuralNetworkTest::test_get_trainable_layers_parameters_number()
{
   cout << "test_get_trainable_layers_parameters_number\n";

   NeuralNetwork neural_network;
   Tensor<Index, 1> layers_parameters_numbers;

   // Test

   Tensor<Index, 1> architecture(3);

   architecture.setValues({1, 2, 3});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   layers_parameters_numbers = neural_network.get_trainable_layers_parameters_numbers();

   assert_true(layers_parameters_numbers.size() == 2, LOG);

   // Test

   architecture.resize(4);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);
   layers_parameters_numbers = neural_network.get_trainable_layers_parameters_numbers();

   assert_true(layers_parameters_numbers.size() == 3, LOG);
}


void NeuralNetworkTest::test_set_parameters()
{
   cout << "test_set_parameters\n";

   Tensor<Index, 1> architecture;
   NeuralNetwork neural_network;

   Index parameters_number;
   Tensor<type, 1> parameters;

   // Test

   neural_network.set_parameters(parameters);

   parameters = neural_network.get_parameters();
   assert_true(parameters.size() == 0, LOG);

   // Test

   architecture.resize(2);

   architecture.setConstant(2);

   neural_network.set(NeuralNetwork::Approximation, architecture);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   neural_network.set_parameters(parameters);

   parameters = neural_network.get_parameters();

   assert_true(parameters.size() == parameters_number, LOG);
   assert_true(parameters[0] == 0.0, LOG);
//   assert_true(parameters[parameters_number-1] - parameters_number - 1.0 < numeric_limits<type>::min(), LOG);
}


void NeuralNetworkTest::test_set_parameters_constant()
{
   cout << "test_set_parameters_constant\n";

   NeuralNetwork neural_network;
   Tensor<type, 1> parameters;
   Tensor<Index, 1> architecture;


   // Test

   architecture.resize(3);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.set_parameters_constant(1.0);
   parameters = neural_network.get_parameters();
//   assert_true(parameters == 1.0, LOG);

   // Test

   architecture.resize(3);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.set_parameters_random();
   parameters = neural_network.get_parameters();
//   assert_true(parameters == 1.0, LOG);
}


void NeuralNetworkTest::test_set_parameters_random()
{
   cout << "test_set_parameters_random\n";

   NeuralNetwork neural_network;
   Tensor<Index, 1> architecture;
   Tensor<type, 1> parameters;

   // Test

   architecture.resize(3);
   architecture.setValues({1, 6, 1});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_random();

//   assert_true(neural_network.get_parameters() >= -1.0, LOG);
//   assert_true(neural_network.get_parameters() <= 1.0, LOG);
}


void NeuralNetworkTest::test_calculate_parameters_norm()
{
   cout << "test_calculate_parameters_norm\n";

   NeuralNetwork neural_network;
   type parameters_norm = 0;
   Tensor<Index, 1> architecture;

   // Test 

   architecture.resize(4);
   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.set_parameters_constant(1.0);

   parameters_norm = neural_network.calculate_parameters_norm();

   assert_true(parameters_norm == sqrt(6.0), LOG);
}


void NeuralNetworkTest::test_calculate_outputs()
{
   cout << "test_calculate_outputs\n";
/*
   NeuralNetwork neural_network;

   Index inputs_number;
   Index outputs_number;

   Tensor<Index, 1> architecture;

   Tensor<type, 2> inputs;
   Tensor<type, 2> outputs;

   Index parameters_number;

   Tensor<type, 1> parameters;

   // Test

   architecture.resize(2);

   architecture.setConstant(3);

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);

   inputs.resize(1,3);

   inputs.setConstant(0.0);

   outputs = neural_network.calculate_outputs(inputs);




   assert_true(outputs.rank() == 2, LOG);
   assert_true(outputs.size() == 3, LOG);
//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(3);

   architecture.setValues({2, 1, 5});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);

   inputs.resize(1, 2);

   inputs.setConstant(0.0);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(outputs.size() == 5, LOG);
//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(2);

   architecture.setValues({1, 2});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs.resize(1, 1);

   inputs.setConstant(2.0);

   neural_network.set_parameters_constant(1.0);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(outputs.size() == 2, LOG);

   // Test

   architecture.resize(3);
   architecture.setValues({4, 3, 3});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs.resize(1, 4);

   inputs.setConstant(0.0);

   neural_network.set_parameters_constant(1.0);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(neural_network.calculate_outputs(inputs).size() == 3, LOG);

   // Test

   architecture.resize(2);

   architecture.setValues({1, 2});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs_number = neural_network.get_inputs_number();
   outputs_number = neural_network.get_outputs_number();

   inputs.resize(1,inputs_number);

   inputs.setConstant(0.0);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   parameters.setConstant(0.0);

   neural_network.set_parameters(parameters);
   outputs = neural_network.calculate_outputs(inputs);

   assert_true(outputs.size() == outputs_number, LOG);
//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(3);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.set_parameters_constant(0.0);

   inputs.resize(1, 1);

   inputs.setConstant(0.0);

   outputs = neural_network.calculate_outputs(inputs);

//   assert_true(outputs == 0.0, LOG);

   // Scaling + Perceptron + Perceptron + Unscaling + Bounding

//   assert_true(neural_network.calculate_outputs(inputs) == 0.0, LOG);
   assert_true(neural_network.calculate_outputs(inputs).size() == 1, LOG);

   // Scaling + Perceptron + Probabilistic

   architecture.resize(2);
   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Classification, architecture);

   neural_network.set_parameters_constant(0.0);

   inputs.resize(1, 1);

   inputs.setConstant(0.0);

   outputs = neural_network.calculate_outputs(inputs);

//   assert_true(neural_network.calculate_outputs(inputs) == 0.5, LOG);
//            || neural_network.calculate_outputs(inputs) == 1.0, LOG);

   inputs.setRandom();

//   assert_true(neural_network.calculate_outputs(inputs) >= 0.0, LOG);
//   assert_true(neural_network.calculate_outputs(inputs) <= 1.0, LOG);
   assert_true(neural_network.calculate_outputs(inputs).dimension(1) == 1, LOG);

   NeuralNetwork neural_network_4;

   const Index categories = 3;
   parameters_number = 5;

   inputs_number = 10;

   ScalingLayer* scaling_layer_3 = new ScalingLayer(inputs_number);
   PerceptronLayer* perceptron_layer_4 = new PerceptronLayer(inputs_number, categories);
   ProbabilisticLayer* probabilistic_layer_5 = new ProbabilisticLayer(categories,categories);

   neural_network_4.add_layer(scaling_layer_3);
   neural_network_4.add_layer(perceptron_layer_4);
   neural_network_4.add_layer(probabilistic_layer_5);

   inputs.resize(parameters_number, inputs_number);

   inputs.setRandom();

//   assert_true(minimum(neural_network_4.calculate_outputs(inputs)) >= 0.0, LOG);
//   assert_true(maximum(neural_network_4.calculate_outputs(inputs)) <= 1.0, LOG);
   assert_true(neural_network_4.calculate_outputs(inputs).size() == parameters_number*categories, LOG);

   // Test

   architecture.resize(3);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);

   inputs.resize(1, 1);

   outputs = neural_network.calculate_outputs(inputs);

//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(5);

   architecture.setRandom();

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs_number = neural_network.get_inputs_number();
   outputs_number = neural_network.get_outputs_number();

   inputs.resize(2,inputs_number);

   inputs.setConstant(0.0);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   parameters.setConstant(0.0);

   neural_network.set_parameters(parameters);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(outputs.dimension(1) == outputs_number, LOG);
//   assert_true(outputs == 0.0, LOG);

   // Test Convolutional
/*
   ConvolutionalLayer* convolutional_layer = new ConvolutionalLayer;
   PoolingLayer* pooling_layer = new PoolingLayer;

   inputs.resize(10,3,28,28);

   inputs.setConstant(0.0);

   convolutional_layer->set({3,28,28}, {5,7,7});
   convolutional_layer->set_parameters(Tensor<type, 1>(740, 0));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::MaxPooling);
   pooling_layer->set_pool_size(2,2);

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);

   outputs = neural_network.calculate_outputs(inputs);

//   assert_true(outputs == 0, LOG);

   // Test

   inputs.resize(2,2,3,3);
   inputs(0,0,0,0) = 1.1;
   inputs(0,0,0,1) = 1.1;
   inputs(0,0,0,2) = 1.1;
   inputs(0,0,1,0) = 1.1;
   inputs(0,0,1,1) = 1.1;
   inputs(0,0,1,2) = 1.1;
   inputs(0,0,2,0) = 1.1;
   inputs(0,0,2,1) = 1.1;
   inputs(0,0,2,2) = 1.1;
   inputs(0,1,0,0) = 1.2;
   inputs(0,1,0,1) = 1.2;
   inputs(0,1,0,2) = 1.2;
   inputs(0,1,1,0) = 1.2;
   inputs(0,1,1,1) = 1.2;
   inputs(0,1,1,2) = 1.2;
   inputs(0,1,2,0) = 1.2;
   inputs(0,1,2,1) = 1.2;
   inputs(0,1,2,2) = 1.2;
   inputs(1,0,0,0) = 2.1;
   inputs(1,0,0,1) = 2.1;
   inputs(1,0,0,2) = 2.1;
   inputs(1,0,1,0) = 2.1;
   inputs(1,0,1,1) = 2.1;
   inputs(1,0,1,2) = 2.1;
   inputs(1,0,2,0) = 2.1;
   inputs(1,0,2,1) = 2.1;
   inputs(1,0,2,2) = 2.1;
   inputs(1,1,0,0) = 2.2;
   inputs(1,1,0,1) = 2.2;
   inputs(1,1,0,2) = 2.2;
   inputs(1,1,1,0) = 2.2;
   inputs(1,1,1,1) = 2.2;
   inputs(1,1,1,2) = 2.2;
   inputs(1,1,2,0) = 2.2;
   inputs(1,1,2,1) = 2.2;
   inputs(1,1,2,2) = 2.2;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::Linear);
   convolutional_layer->set({2,3,3}, {5,2,2});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,1,1,1,1,-1,0,4,1,1,0,1,3,2,3,0,0,2,4,9,0,0,2,2,2,0,1,3,4,4,1,0,4,1,1,-1,1,1,1,1,
                                                      -2,-1,0,1,2}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::NoPooling);

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(abs(outputs(0,0,0,0) + 2.2) < 1e-6 &&
               abs(outputs(0,0,0,1) + 2.2) < 1e-6 &&
               abs(outputs(0,0,1,0) + 2.2) < 1e-6 &&
               abs(outputs(0,0,1,1) + 2.2) < 1e-6 &&
               abs(outputs(0,1,0,0) - 3.6) < 1e-6 &&
               abs(outputs(0,1,0,1) - 3.6) < 1e-6 &&
               abs(outputs(0,1,1,0) - 3.6) < 1e-6 &&
               abs(outputs(0,1,1,1) - 3.6) < 1e-6 &&
               abs(outputs(0,2,0,0) - 23) < 1e-6 &&
               abs(outputs(0,2,0,1) - 23) < 1e-6 &&
               abs(outputs(0,2,1,0) - 23) < 1e-6 &&
               abs(outputs(0,2,1,1) - 23) < 1e-6 &&
               abs(outputs(0,3,0,0) - 19.6) < 1e-6 &&
               abs(outputs(0,3,0,1) - 19.6) < 1e-6 &&
               abs(outputs(0,3,1,0) - 19.6) < 1e-6 &&
               abs(outputs(0,3,1,1) - 19.6) < 1e-6 &&
               abs(outputs(0,4,0,0) - 27.7) < 1e-6 &&
               abs(outputs(0,4,0,1) - 27.7) < 1e-6 &&
               abs(outputs(0,4,1,0) - 27.7) < 1e-6 &&
               abs(outputs(0,4,1,1) - 27.7) < 1e-6 &&
               abs(outputs(1,0,0,0) + 2.2) < 1e-6 &&
               abs(outputs(1,0,0,1) + 2.2) < 1e-6 &&
               abs(outputs(1,0,1,0) + 2.2) < 1e-6 &&
               abs(outputs(1,0,1,1) + 2.2) < 1e-6 &&
               abs(outputs(1,1,0,0) - 7.6) < 1e-6 &&
               abs(outputs(1,1,0,1) - 7.6) < 1e-6 &&
               abs(outputs(1,1,1,0) - 7.6) < 1e-6 &&
               abs(outputs(1,1,1,1) - 7.6) < 1e-6 &&
               abs(outputs(1,2,0,0) - 43) < 1e-6 &&
               abs(outputs(1,2,0,1) - 43) < 1e-6 &&
               abs(outputs(1,2,1,0) - 43) < 1e-6 &&
               abs(outputs(1,2,1,1) - 43) < 1e-6 &&
               abs(outputs(1,3,0,0) - 35.6) < 1e-6 &&
               abs(outputs(1,3,0,1) - 35.6) < 1e-6 &&
               abs(outputs(1,3,1,0) - 35.6) < 1e-6 &&
               abs(outputs(1,3,1,1) - 35.6) < 1e-6 &&
               abs(outputs(1,4,0,0) - 49.7) < 1e-6 &&
               abs(outputs(1,4,0,1) - 49.7) < 1e-6 &&
               abs(outputs(1,4,1,0) - 49.7) < 1e-6 &&
               abs(outputs(1,4,1,1) - 49.7) < 1e-6, LOG);

   // Test

   inputs.resize(2,2,3,3);
   inputs(0,0,0,0) = 1.1;
   inputs(0,0,0,1) = 1.1;
   inputs(0,0,0,2) = 1.1;
   inputs(0,0,1,0) = 1.1;
   inputs(0,0,1,1) = 1.1;
   inputs(0,0,1,2) = 1.1;
   inputs(0,0,2,0) = 1.1;
   inputs(0,0,2,1) = 1.1;
   inputs(0,0,2,2) = 1.1;
   inputs(0,1,0,0) = 1.2;
   inputs(0,1,0,1) = 1.2;
   inputs(0,1,0,2) = 1.2;
   inputs(0,1,1,0) = 1.2;
   inputs(0,1,1,1) = 1.2;
   inputs(0,1,1,2) = 1.2;
   inputs(0,1,2,0) = 1.2;
   inputs(0,1,2,1) = 1.2;
   inputs(0,1,2,2) = 1.2;
   inputs(1,0,0,0) = 2.1;
   inputs(1,0,0,1) = 2.1;
   inputs(1,0,0,2) = 2.1;
   inputs(1,0,1,0) = 2.1;
   inputs(1,0,1,1) = 2.1;
   inputs(1,0,1,2) = 2.1;
   inputs(1,0,2,0) = 2.1;
   inputs(1,0,2,1) = 2.1;
   inputs(1,0,2,2) = 2.1;
   inputs(1,1,0,0) = 2.2;
   inputs(1,1,0,1) = 2.2;
   inputs(1,1,0,2) = 2.2;
   inputs(1,1,1,0) = 2.2;
   inputs(1,1,1,1) = 2.2;
   inputs(1,1,1,2) = 2.2;
   inputs(1,1,2,0) = 2.2;
   inputs(1,1,2,1) = 2.2;
   inputs(1,1,2,2) = 2.2;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::Linear);
   convolutional_layer->set({2,3,3}, {5,2,2});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,1,1,1,1,-1,0,4,1,1,0,1,3,2,3,0,0,2,4,9,0,0,2,2,2,0,1,3,4,4,1,0,4,1,1,-1,1,1,1,1,
                                                      -2,-1,0,1,2}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::MaxPooling);
   pooling_layer->set_pool_size(2,2);

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(abs(outputs(0,0,0,0) + 2.2) < 1e-6 &&
               abs(outputs(0,1,0,0) - 3.6) < 1e-6 &&
               abs(outputs(0,2,0,0) - 23) < 1e-6 &&
               abs(outputs(0,3,0,0) - 19.6) < 1e-6 &&
               abs(outputs(0,4,0,0) - 27.7) < 1e-6 &&
               abs(outputs(1,0,0,0) + 2.2) < 1e-6 &&
               abs(outputs(1,1,0,0) - 7.6) < 1e-6 &&
               abs(outputs(1,2,0,0) - 43) < 1e-6 &&
               abs(outputs(1,3,0,0) - 35.6) < 1e-6 &&
               abs(outputs(1,4,0,0) - 49.7) < 1e-6, LOG);

   // Test

   inputs.resize(2,2,3,3);
   inputs(0,0,0,0) = 1.1;
   inputs(0,0,0,1) = 1.1;
   inputs(0,0,0,2) = 1.1;
   inputs(0,0,1,0) = 1.1;
   inputs(0,0,1,1) = 1.1;
   inputs(0,0,1,2) = 1.1;
   inputs(0,0,2,0) = 1.1;
   inputs(0,0,2,1) = 1.1;
   inputs(0,0,2,2) = 1.1;
   inputs(0,1,0,0) = 1.2;
   inputs(0,1,0,1) = 1.2;
   inputs(0,1,0,2) = 1.2;
   inputs(0,1,1,0) = 1.2;
   inputs(0,1,1,1) = 1.2;
   inputs(0,1,1,2) = 1.2;
   inputs(0,1,2,0) = 1.2;
   inputs(0,1,2,1) = 1.2;
   inputs(0,1,2,2) = 1.2;
   inputs(1,0,0,0) = 2.1;
   inputs(1,0,0,1) = 2.1;
   inputs(1,0,0,2) = 2.1;
   inputs(1,0,1,0) = 2.1;
   inputs(1,0,1,1) = 2.1;
   inputs(1,0,1,2) = 2.1;
   inputs(1,0,2,0) = 2.1;
   inputs(1,0,2,1) = 2.1;
   inputs(1,0,2,2) = 2.1;
   inputs(1,1,0,0) = 2.2;
   inputs(1,1,0,1) = 2.2;
   inputs(1,1,0,2) = 2.2;
   inputs(1,1,1,0) = 2.2;
   inputs(1,1,1,1) = 2.2;
   inputs(1,1,1,2) = 2.2;
   inputs(1,1,2,0) = 2.2;
   inputs(1,1,2,1) = 2.2;
   inputs(1,1,2,2) = 2.2;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::Linear);
   convolutional_layer->set({2,3,3}, {5,2,2});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,1,1,1,1,-1,0,4,1,1,0,1,3,2,3,0,0,2,4,9,0,0,2,2,2,0,1,3,4,4,1,0,4,1,1,-1,1,1,1,1,
                                                      -2,-1,0,1,2}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::AveragePooling);
   pooling_layer->set_pool_size(2,2);

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(abs(outputs(0,0,0,0) + 2.2) < 1e-6 &&
               abs(outputs(0,1,0,0) - 3.6) < 1e-6 &&
               abs(outputs(0,2,0,0) - 23) < 1e-6 &&
               abs(outputs(0,3,0,0) - 19.6) < 1e-6 &&
               abs(outputs(0,4,0,0) - 27.7) < 1e-6 &&
               abs(outputs(1,0,0,0) + 2.2) < 1e-6 &&
               abs(outputs(1,1,0,0) - 7.6) < 1e-6 &&
               abs(outputs(1,2,0,0) - 43) < 1e-6 &&
               abs(outputs(1,3,0,0) - 35.6) < 1e-6 &&
               abs(outputs(1,4,0,0) - 49.7) < 1e-6, LOG);

   // Test

   inputs.resize(2,1,6,6);
   inputs(0,0,0,0) = 1;
   inputs(0,0,0,1) = 2;
   inputs(0,0,0,2) = 3;
   inputs(0,0,0,3) = 4;
   inputs(0,0,0,4) = 5;
   inputs(0,0,0,5) = 6;
   inputs(0,0,1,0) = 7;
   inputs(0,0,1,1) = 8;
   inputs(0,0,1,2) = 9;
   inputs(0,0,1,3) = 10;
   inputs(0,0,1,4) = 11;
   inputs(0,0,1,5) = 12;
   inputs(0,0,2,0) = 13;
   inputs(0,0,2,1) = 14;
   inputs(0,0,2,2) = 15;
   inputs(0,0,2,3) = 16;
   inputs(0,0,2,4) = 17;
   inputs(0,0,2,5) = 18;
   inputs(0,0,3,0) = 19;
   inputs(0,0,3,1) = 20;
   inputs(0,0,3,2) = 21;
   inputs(0,0,3,3) = 22;
   inputs(0,0,3,4) = 23;
   inputs(0,0,3,5) = 24;
   inputs(0,0,4,0) = 25;
   inputs(0,0,4,1) = 26;
   inputs(0,0,4,2) = 27;
   inputs(0,0,4,3) = 28;
   inputs(0,0,4,4) = 29;
   inputs(0,0,4,5) = 30;
   inputs(0,0,5,0) = 31;
   inputs(0,0,5,1) = 32;
   inputs(0,0,5,2) = 33;
   inputs(0,0,5,3) = 34;
   inputs(0,0,5,4) = 35;
   inputs(0,0,5,5) = 36;
   inputs(1,0,0,0) = -1;
   inputs(1,0,0,1) = -2;
   inputs(1,0,0,2) = -3;
   inputs(1,0,0,3) = -4;
   inputs(1,0,0,4) = -5;
   inputs(1,0,0,5) = -6;
   inputs(1,0,1,0) = -7;
   inputs(1,0,1,1) = -8;
   inputs(1,0,1,2) = -9;
   inputs(1,0,1,3) = -10;
   inputs(1,0,1,4) = -11;
   inputs(1,0,1,5) = -12;
   inputs(1,0,2,0) = -13;
   inputs(1,0,2,1) = -14;
   inputs(1,0,2,2) = -15;
   inputs(1,0,2,3) = -16;
   inputs(1,0,2,4) = -17;
   inputs(1,0,2,5) = -18;
   inputs(1,0,3,0) = -19;
   inputs(1,0,3,1) = -20;
   inputs(1,0,3,2) = -21;
   inputs(1,0,3,3) = -22;
   inputs(1,0,3,4) = -23;
   inputs(1,0,3,5) = -24;
   inputs(1,0,4,0) = -25;
   inputs(1,0,4,1) = -26;
   inputs(1,0,4,2) = -27;
   inputs(1,0,4,3) = -28;
   inputs(1,0,4,4) = -29;
   inputs(1,0,4,5) = -30;
   inputs(1,0,5,0) = -31;
   inputs(1,0,5,1) = -32;
   inputs(1,0,5,2) = -33;
   inputs(1,0,5,3) = -34;
   inputs(1,0,5,4) = -35;
   inputs(1,0,5,5) = -36;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::RectifiedLinear);
   convolutional_layer->set({1,6,6}, {3,3,3});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,-1,0,1}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::AveragePooling);
   pooling_layer->set_pool_size(2,2);

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(outputs(0,0,0,0) == 102.5 &&
               outputs(0,0,0,1) == 111.5 &&
               outputs(0,0,0,2) == 120.5 &&
               outputs(0,0,1,0) == 156.5 &&
               outputs(0,0,1,1) == 165.5 &&
               outputs(0,0,1,2) == 174.5 &&
               outputs(0,0,2,0) == 210.5 &&
               outputs(0,0,2,1) == 219.5 &&
               outputs(0,0,2,2) == 228.5 &&
               outputs(0,1,0,0) == 207.0 &&
               outputs(0,1,0,1) == 225.0 &&
               outputs(0,1,0,2) == 243.0 &&
               outputs(0,1,1,0) == 315.0 &&
               outputs(0,1,1,1) == 333.0 &&
               outputs(0,1,1,2) == 351.0 &&
               outputs(0,1,2,0) == 423.0 &&
               outputs(0,1,2,1) == 441.0 &&
               outputs(0,1,2,2) == 459.0 &&
               outputs(0,2,0,0) == 311.5 &&
               outputs(0,2,0,1) == 338.5 &&
               outputs(0,2,0,2) == 365.5 &&
               outputs(0,2,1,0) == 473.5 &&
               outputs(0,2,1,1) == 500.5 &&
               outputs(0,2,1,2) == 527.5 &&
               outputs(0,2,2,0) == 635.5 &&
               outputs(0,2,2,1) == 662.5 &&
               outputs(0,2,2,2) == 689.5 &&
               outputs(1,0,0,0) == 0.0 &&
               outputs(1,0,0,1) == 0.0 &&
               outputs(1,0,0,2) == 0.0 &&
               outputs(1,0,1,0) == 0.0 &&
               outputs(1,0,1,1) == 0.0 &&
               outputs(1,0,1,2) == 0.0 &&
               outputs(1,0,2,0) == 0.0 &&
               outputs(1,0,2,1) == 0.0 &&
               outputs(1,0,2,2) == 0.0 &&
               outputs(1,1,0,0) == 0.0 &&
               outputs(1,1,0,1) == 0.0 &&
               outputs(1,1,0,2) == 0.0 &&
               outputs(1,1,1,0) == 0.0 &&
               outputs(1,1,1,1) == 0.0 &&
               outputs(1,1,1,2) == 0.0 &&
               outputs(1,1,2,0) == 0.0 &&
               outputs(1,1,2,1) == 0.0 &&
               outputs(1,1,2,2) == 0.0 &&
               outputs(1,2,0,0) == 0.0 &&
               outputs(1,2,0,1) == 0.0 &&
               outputs(1,2,0,2) == 0.0 &&
               outputs(1,2,1,0) == 0.0 &&
               outputs(1,2,1,1) == 0.0 &&
               outputs(1,2,1,2) == 0.0 &&
               outputs(1,2,2,0) == 0.0 &&
               outputs(1,2,2,1) == 0.0 &&
               outputs(1,2,2,2) == 0.0, LOG);

   // Test

   inputs.resize(2,1,6,6);
   inputs(0,0,0,0) = 1;
   inputs(0,0,0,1) = 2;
   inputs(0,0,0,2) = 3;
   inputs(0,0,0,3) = 4;
   inputs(0,0,0,4) = 5;
   inputs(0,0,0,5) = 6;
   inputs(0,0,1,0) = 7;
   inputs(0,0,1,1) = 8;
   inputs(0,0,1,2) = 9;
   inputs(0,0,1,3) = 10;
   inputs(0,0,1,4) = 11;
   inputs(0,0,1,5) = 12;
   inputs(0,0,2,0) = 13;
   inputs(0,0,2,1) = 14;
   inputs(0,0,2,2) = 15;
   inputs(0,0,2,3) = 16;
   inputs(0,0,2,4) = 17;
   inputs(0,0,2,5) = 18;
   inputs(0,0,3,0) = 19;
   inputs(0,0,3,1) = 20;
   inputs(0,0,3,2) = 21;
   inputs(0,0,3,3) = 22;
   inputs(0,0,3,4) = 23;
   inputs(0,0,3,5) = 24;
   inputs(0,0,4,0) = 25;
   inputs(0,0,4,1) = 26;
   inputs(0,0,4,2) = 27;
   inputs(0,0,4,3) = 28;
   inputs(0,0,4,4) = 29;
   inputs(0,0,4,5) = 30;
   inputs(0,0,5,0) = 31;
   inputs(0,0,5,1) = 32;
   inputs(0,0,5,2) = 33;
   inputs(0,0,5,3) = 34;
   inputs(0,0,5,4) = 35;
   inputs(0,0,5,5) = 36;
   inputs(1,0,0,0) = -1;
   inputs(1,0,0,1) = -2;
   inputs(1,0,0,2) = -3;
   inputs(1,0,0,3) = -4;
   inputs(1,0,0,4) = -5;
   inputs(1,0,0,5) = -6;
   inputs(1,0,1,0) = -7;
   inputs(1,0,1,1) = -8;
   inputs(1,0,1,2) = -9;
   inputs(1,0,1,3) = -10;
   inputs(1,0,1,4) = -11;
   inputs(1,0,1,5) = -12;
   inputs(1,0,2,0) = -13;
   inputs(1,0,2,1) = -14;
   inputs(1,0,2,2) = -15;
   inputs(1,0,2,3) = -16;
   inputs(1,0,2,4) = -17;
   inputs(1,0,2,5) = -18;
   inputs(1,0,3,0) = -19;
   inputs(1,0,3,1) = -20;
   inputs(1,0,3,2) = -21;
   inputs(1,0,3,3) = -22;
   inputs(1,0,3,4) = -23;
   inputs(1,0,3,5) = -24;
   inputs(1,0,4,0) = -25;
   inputs(1,0,4,1) = -26;
   inputs(1,0,4,2) = -27;
   inputs(1,0,4,3) = -28;
   inputs(1,0,4,4) = -29;
   inputs(1,0,4,5) = -30;
   inputs(1,0,5,0) = -31;
   inputs(1,0,5,1) = -32;
   inputs(1,0,5,2) = -33;
   inputs(1,0,5,3) = -34;
   inputs(1,0,5,4) = -35;
   inputs(1,0,5,5) = -36;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::SoftSign);
   convolutional_layer->set({1,6,6}, {3,3,3});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,-1,0,1}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::MaxPooling);
   pooling_layer->set_pool_size(2,2);

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(abs(outputs(0,0,0,0) - 0.992593) < 1e-6 &&
               abs(outputs(0,0,0,1) - 0.993056) < 1e-6 &&
               abs(outputs(0,0,0,2) - 0.993464) < 1e-6 &&
               abs(outputs(0,0,1,0) - 0.994709) < 1e-6 &&
               abs(outputs(0,0,1,1) - 0.994949) < 1e-6 &&
               abs(outputs(0,0,1,2) - 0.995169) < 1e-6 &&
               abs(outputs(0,0,2,0) - 0.995885) < 1e-6 &&
               abs(outputs(0,0,2,1) - 0.996032) < 1e-6 &&
               abs(outputs(0,0,2,2) - 0.996169) < 1e-6 &&
               abs(outputs(0,1,0,0) - 0.996310) < 1e-6 &&
               abs(outputs(0,1,0,1) - 0.996540) < 1e-6 &&
               abs(outputs(0,1,0,2) - 0.996743) < 1e-6 &&
               abs(outputs(0,1,1,0) - 0.997361) < 1e-6 &&
               abs(outputs(0,1,1,1) - 0.997481) < 1e-6 &&
               abs(outputs(0,1,1,2) - 0.997590) < 1e-6 &&
               abs(outputs(0,1,2,0) - 0.997947) < 1e-6 &&
               abs(outputs(0,1,2,1) - 0.998020) < 1e-6 &&
               abs(outputs(0,1,2,2) - 0.998088) < 1e-6 &&
               abs(outputs(0,2,0,0) - 0.997543) < 1e-6 &&
               abs(outputs(0,2,0,1) - 0.997696) < 1e-6 &&
               abs(outputs(0,2,0,2) - 0.997831) < 1e-6 &&
               abs(outputs(0,2,1,0) - 0.998243) < 1e-6 &&
               abs(outputs(0,2,1,1) - 0.998322) < 1e-6 &&
               abs(outputs(0,2,1,2) - 0.998395) < 1e-6 &&
               abs(outputs(0,2,2,0) - 0.998632) < 1e-6 &&
               abs(outputs(0,2,2,1) - 0.998681) < 1e-6 &&
               abs(outputs(0,2,2,2) - 0.998726) < 1e-6 &&
               abs(outputs(1,0,0,0) + 0.986486) < 1e-6 &&
               abs(outputs(1,0,0,1) + 0.987952) < 1e-6 &&
               abs(outputs(1,0,0,2) + 0.989130) < 1e-6 &&
               abs(outputs(1,0,1,0) + 0.992188) < 1e-6 &&
               abs(outputs(1,0,1,1) + 0.992701) < 1e-6 &&
               abs(outputs(1,0,1,2) + 0.993151) < 1e-6 &&
               abs(outputs(1,0,2,0) + 0.994505) < 1e-6 &&
               abs(outputs(1,0,2,1) + 0.994764) < 1e-6 &&
               abs(outputs(1,0,2,2) + 0.995000) < 1e-6 &&
               abs(outputs(1,1,0,0) + 0.993103) < 1e-6 &&
               abs(outputs(1,1,0,1) + 0.993865) < 1e-6 &&
               abs(outputs(1,1,0,2) + 0.994475) < 1e-6 &&
               abs(outputs(1,1,1,0) + 0.996047) < 1e-6 &&
               abs(outputs(1,1,1,1) + 0.996310) < 1e-6 &&
               abs(outputs(1,1,1,2) + 0.996540) < 1e-6 &&
               abs(outputs(1,1,2,0) + 0.997230) < 1e-6 &&
               abs(outputs(1,1,2,1) + 0.997361) < 1e-6 &&
               abs(outputs(1,1,2,2) + 0.997481) < 1e-6 &&
               abs(outputs(1,2,0,0) + 0.995370) < 1e-6 &&
               abs(outputs(1,2,0,1) + 0.995885) < 1e-6 &&
               abs(outputs(1,2,0,2) + 0.996296) < 1e-6 &&
               abs(outputs(1,2,1,0) + 0.997354) < 1e-6 &&
               abs(outputs(1,2,1,1) + 0.997531) < 1e-6 &&
               abs(outputs(1,2,1,2) + 0.997685) < 1e-6 &&
               abs(outputs(1,2,2,0) + 0.998148) < 1e-6 &&
               abs(outputs(1,2,2,1) + 0.998236) < 1e-6 &&
               abs(outputs(1,2,2,2) + 0.998316) < 1e-6, LOG);

   // Test

   PerceptronLayer* perceptron_layer = new PerceptronLayer;

   inputs.resize(2,2,3,3);
   inputs(0,0,0,0) = 1.1;
   inputs(0,0,0,1) = 1.1;
   inputs(0,0,0,2) = 1.1;
   inputs(0,0,1,0) = 1.1;
   inputs(0,0,1,1) = 1.1;
   inputs(0,0,1,2) = 1.1;
   inputs(0,0,2,0) = 1.1;
   inputs(0,0,2,1) = 1.1;
   inputs(0,0,2,2) = 1.1;
   inputs(0,1,0,0) = 1.2;
   inputs(0,1,0,1) = 1.2;
   inputs(0,1,0,2) = 1.2;
   inputs(0,1,1,0) = 1.2;
   inputs(0,1,1,1) = 1.2;
   inputs(0,1,1,2) = 1.2;
   inputs(0,1,2,0) = 1.2;
   inputs(0,1,2,1) = 1.2;
   inputs(0,1,2,2) = 1.2;
   inputs(1,0,0,0) = 2.1;
   inputs(1,0,0,1) = 2.1;
   inputs(1,0,0,2) = 2.1;
   inputs(1,0,1,0) = 2.1;
   inputs(1,0,1,1) = 2.1;
   inputs(1,0,1,2) = 2.1;
   inputs(1,0,2,0) = 2.1;
   inputs(1,0,2,1) = 2.1;
   inputs(1,0,2,2) = 2.1;
   inputs(1,1,0,0) = 2.2;
   inputs(1,1,0,1) = 2.2;
   inputs(1,1,0,2) = 2.2;
   inputs(1,1,1,0) = 2.2;
   inputs(1,1,1,1) = 2.2;
   inputs(1,1,1,2) = 2.2;
   inputs(1,1,2,0) = 2.2;
   inputs(1,1,2,1) = 2.2;
   inputs(1,1,2,2) = 2.2;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::Linear);
   convolutional_layer->set({2,3,3}, {5,2,2});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,1,1,1,1,-1,0,4,1,1,0,1,3,2,3,0,0,2,4,9,0,0,2,2,2,0,1,3,4,4,1,0,4,1,1,-1,1,1,1,1,
                                                      -2,-1,0,1,2}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::NoPooling);

   perceptron_layer->set(20, 1, OpenNN::PerceptronLayer::Linear);
   perceptron_layer->set_parameters({1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-1});

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);
   neural_network.add_layer(perceptron_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(abs(outputs(0,0) - 285.8) < 1e-6 &&
               abs(outputs(1,0) - 533.8) < 1e-6, LOG);

   // Test Convolutional

   inputs.resize(2,2,3,3);
   inputs(0,0,0,0) = 1.1;
   inputs(0,0,0,1) = 1.1;
   inputs(0,0,0,2) = 1.1;
   inputs(0,0,1,0) = 1.1;
   inputs(0,0,1,1) = 1.1;
   inputs(0,0,1,2) = 1.1;
   inputs(0,0,2,0) = 1.1;
   inputs(0,0,2,1) = 1.1;
   inputs(0,0,2,2) = 1.1;
   inputs(0,1,0,0) = 1.2;
   inputs(0,1,0,1) = 1.2;
   inputs(0,1,0,2) = 1.2;
   inputs(0,1,1,0) = 1.2;
   inputs(0,1,1,1) = 1.2;
   inputs(0,1,1,2) = 1.2;
   inputs(0,1,2,0) = 1.2;
   inputs(0,1,2,1) = 1.2;
   inputs(0,1,2,2) = 1.2;
   inputs(1,0,0,0) = 2.1;
   inputs(1,0,0,1) = 2.1;
   inputs(1,0,0,2) = 2.1;
   inputs(1,0,1,0) = 2.1;
   inputs(1,0,1,1) = 2.1;
   inputs(1,0,1,2) = 2.1;
   inputs(1,0,2,0) = 2.1;
   inputs(1,0,2,1) = 2.1;
   inputs(1,0,2,2) = 2.1;
   inputs(1,1,0,0) = 2.2;
   inputs(1,1,0,1) = 2.2;
   inputs(1,1,0,2) = 2.2;
   inputs(1,1,1,0) = 2.2;
   inputs(1,1,1,1) = 2.2;
   inputs(1,1,1,2) = 2.2;
   inputs(1,1,2,0) = 2.2;
   inputs(1,1,2,1) = 2.2;
   inputs(1,1,2,2) = 2.2;

   convolutional_layer->set_activation_function(OpenNN::ConvolutionalLayer::Linear);
   convolutional_layer->set({2,3,3}, {5,2,2});
   convolutional_layer->set_parameters(Tensor<type, 1>({1,1,1,1,1,-1,0,4,1,1,0,1,3,2,3,0,0,2,4,9,0,0,2,2,2,0,1,3,4,4,1,0,4,1,1,-1,1,1,1,1,
                                                      -2,-1,0,1,2}));

   pooling_layer->set_pooling_method(OpenNN::PoolingLayer::MaxPooling);
   pooling_layer->set_pool_size(2, 2);

   perceptron_layer->set(5, 1, OpenNN::PerceptronLayer::RectifiedLinear);
   perceptron_layer->set_parameters({1,2,3,4,5,-100});

   neural_network.set();
   neural_network.add_layer(convolutional_layer);
   neural_network.add_layer(pooling_layer);
   neural_network.add_layer(perceptron_layer);

   outputs = neural_network.calculate_outputs(inputs);

   assert_true(abs(outputs(0,0) - 190.9) < 1e-6 &&
               abs(outputs(1,0) - 432.9) < 1e-6, LOG);
*/
}

void NeuralNetworkTest::test_calculate_trainable_outputs()
{
   cout << "test_calculate_trainable_outputs\n";

   NeuralNetwork neural_network;

   Index inputs_number;
   Index outputs_number;

   Tensor<Index, 1> architecture;

   Tensor<type, 2> inputs;
   Tensor<type, 2> outputs;
   Tensor<type, 2> trainable_outputs;

   Index parameters_number;

   Tensor<type, 1> parameters;

   // Test

   architecture.resize(3);

   architecture.setValues({3, 4, 2});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);

   inputs.resize(2,3);

   inputs.setConstant(0.0);

   trainable_outputs = neural_network.calculate_trainable_outputs(inputs);

   assert_true(trainable_outputs.rank() == 2, LOG);
//   assert_true(trainable_outputs == 0.0, LOG);

   // Test

   architecture.resize(3);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0.0);

   inputs.resize(1, 1);

   inputs.setConstant(0.0);

   outputs = neural_network.calculate_outputs(inputs);

//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(3);

   architecture.setValues({4, 3, 5});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs.resize(1, 4);
   inputs.setRandom();

   parameters = neural_network.get_parameters();

//   assert_true(neural_network.calculate_trainable_outputs(inputs)
//            == neural_network.calculate_trainable_outputs(inputs, parameters), LOG);

   // Test

   architecture.resize(3);

   architecture.setValues({1, 2, 5});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs.resize(2, 1);

   inputs.setConstant(0.0);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   parameters.setConstant(0.0);

   outputs = neural_network.calculate_trainable_outputs(inputs, parameters);

   assert_true(outputs.dimension(1)== 5, LOG);

   // Test

   architecture.resize(2);

   architecture.setValues({2, 1});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs_number = neural_network.get_inputs_number();
   outputs_number = neural_network.get_outputs_number();

   inputs.resize(3,inputs_number);

   inputs.setConstant(0.0);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   parameters.setConstant(0.0);

   outputs = neural_network.calculate_trainable_outputs(inputs, parameters);

   assert_true(outputs.dimension(1) == outputs_number, LOG);
//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(2);

   architecture.setValues({2, 4});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.set_parameters_constant(0.0);

   inputs.resize(3, 2);

   inputs.setConstant(0.0);

   outputs = neural_network.calculate_outputs(inputs);

//   assert_true(outputs == 0.0, LOG);

   // Scaling + Perceptron + Perceptron + Unscaling + Bounding

   architecture.resize(3);

   architecture.setValues({2, 4, 3});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.set_parameters_constant(0.0);

   inputs.resize(1, 2);

   inputs.setConstant(0.0);

//   assert_true(neural_network.calculate_outputs(inputs) == 0.0, LOG);
   assert_true(neural_network.calculate_outputs(inputs).dimension(1) == 3, LOG);

   // Scaling + Perceptron + Probabilistic

   architecture.resize(2);

   architecture.setConstant(1);

   neural_network.set(NeuralNetwork::Classification, architecture);

   inputs.resize(1, 1);

   inputs.setConstant(0.0);

//   assert_true(neural_network.calculate_outputs(inputs) >=0 &&
//               neural_network.calculate_outputs(inputs) <= 1, LOG);

   inputs.setRandom();

//   assert_true(neural_network.calculate_outputs(inputs) >= 0.0, LOG);
//   assert_true(neural_network.calculate_outputs(inputs) <= 1.0, LOG);
   assert_true(neural_network.calculate_outputs(inputs).dimension(1) == 1, LOG);

   // Test

   architecture.resize(3);

   architecture.setValues({4, 3, 5});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs.resize(1, 4);
   inputs.setRandom();

   parameters = neural_network.get_parameters();

//   assert_true(neural_network.calculate_trainable_outputs(inputs)
//            == neural_network.calculate_trainable_outputs(inputs, parameters), LOG);

   // Test

   architecture.resize(3);

   architecture.setValues({4, 3, 5});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs.resize(2,4);

   inputs.setConstant(0.0);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   parameters.setConstant(0.0);

   outputs = neural_network.calculate_trainable_outputs(inputs, parameters);

   assert_true(outputs.dimension(1) == 5, LOG);
//   assert_true(outputs == 0.0, LOG);

   // Test

   architecture.resize(5);

   architecture.setRandom();

   neural_network.set(NeuralNetwork::Approximation, architecture);

   inputs_number = neural_network.get_inputs_number();
   outputs_number = neural_network.get_outputs_number();

   inputs.resize(2,inputs_number);

   inputs.setConstant(0.0);

   parameters_number = neural_network.get_parameters_number();

   parameters.resize(parameters_number);

   parameters.setConstant(0.0);

   outputs = neural_network.calculate_trainable_outputs(inputs, parameters);

   assert_true(outputs.dimension(1) == outputs_number, LOG);
//   assert_true(outputs == 0.0, LOG);
}


void NeuralNetworkTest::test_to_XML()
{
   cout << "test_to_XML\n";
/*
   NeuralNetwork neural_network;

   tinyxml2::XMLDocument* document;
   
   // Test
   
   document = neural_network.to_XML();

   assert_true(document != nullptr, LOG);

   delete document;
   */
}


void NeuralNetworkTest::test_from_XML()
{
   cout << "test_from_XML\n";
}


void NeuralNetworkTest::test_print()
{
   cout << "test_print\n";

   // Empty neural network
 
   NeuralNetwork neural_network;

   Tensor<Index, 1> architecture;

   //neural_network.print();

   // Only network architecture

   architecture.resize(3);
   architecture.setValues({2, 4, 3});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   //neural_network.print();
}


void NeuralNetworkTest::test_save()
{
   cout << "test_save\n";

   string file_name = "../data/neural_network.xml";

   NeuralNetwork neural_network;

   Tensor<Index, 1> architecture;

   // Empty multilayer perceptron
 
   neural_network.set();
   neural_network.save(file_name);

   // Only network architecture

   architecture.resize(3);

   architecture.setValues({2, 4, 3});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.save(file_name);

   architecture.resize(3);

   architecture.setValues({1, 1, 1});

   neural_network.set(NeuralNetwork::Approximation, architecture);

   neural_network.save(file_name);
}

void NeuralNetworkTest::test_load()
{
   cout << "test_load\n";

   string file_name = "../data/neural_network.xml";

   // Empty neural network

   NeuralNetwork neural_network;
   neural_network.save(file_name);
   neural_network.load(file_name);
}

void NeuralNetworkTest::test_write_expression()
{
   cout << "test_write_expression\n";

   NeuralNetwork neural_network;
   string expression;

   Tensor<Index, 1> architecture;

   // Test

//   expression = neural_network.write_expression();

   // Test

   architecture.resize(3);

   architecture.setValues({1, 1, 1});


   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(-1.0);
//   expression = neural_network.write_expression();

   // Test

   architecture.resize(3);

   architecture.setValues({2, 1, 1});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(-1.0);
//   expression = neural_network.write_expression();

   // Test

   architecture.setValues({1, 2, 1});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(-1.0);
//   expression = neural_network.write_expression();

   // Test


   architecture.setValues({1, 1, 2});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(-1.0);
//   expression = neural_network.write_expression();

   // Test

   architecture.setValues({2, 2, 2});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(-1.0);
//   expression = neural_network.write_expression();

}



void NeuralNetworkTest::test_forward_propagate()
{
    int n = omp_get_max_threads();

    cout << "Threads: " << n << endl;

    NonBlockingThreadPool simple_thread_pool(n);

    ThreadPoolDevice thread_pool_device(&simple_thread_pool, n);

    const Index inputs_number = 2;
    const Index target_number = 1;

    Tensor<Index, 1>architecture(2);

    architecture.setValues({inputs_number,target_number});

    Tensor<type,2> data(10, 3);

    data.setConstant(1);

    //DataSet

    DataSet dataset(data);

    dataset.set_training();

//    dataset.set_batch_instances_number(5);
/*
    DataSet::Batch batch(5, &dataset);

    Tensor<Index,2> batches_indices = dataset.get_training_batches(false);

    Tensor<Index,1> inputs_indices = dataset.get_input_variables_indices();

    Tensor<Index,1> targets_indices = dataset.get_target_variables_indices();

//    batch.fill(batches_indices.chip(0,0), inputs_indices, targets_indices);

    //NeuralNetwork

    NeuralNetwork neural_network(NeuralNetwork::Approximation, architecture);

    PerceptronLayer* perceptron_layer = dynamic_cast<PerceptronLayer*>(neural_network.get_layer_pointer(1));

    const Index neurons_number = perceptron_layer->get_neurons_number();

    Tensor<type, 2> biases_perceptron(neurons_number, 1);

    biases_perceptron.setConstant(1);

    Tensor<type, 2> synaptic_weights_perceptron(inputs_number, neurons_number);

    synaptic_weights_perceptron.setConstant(1);

    perceptron_layer->set_biases(biases_perceptron);

    perceptron_layer->set_synaptic_weights(synaptic_weights_perceptron);

//    NeuralNetwork::ForwardPropagation forward_propagation(dataset.get_batch_instances_number(), &neural_network);

//    neural_network.forward_propagate(thread_pool_device, batch, forward_propagation);

//    Tensor<type, 2>perceptron_combinations = forward_propagation.layers[0].combinations_2d;

//    assert_true(perceptron_combinations.size() == 5 && perceptron_combinations(0,0) == 3, LOG);
*/
}


void NeuralNetworkTest::run_test_case()
{
   cout << "Running neural network test case...\n";

   // Constructor and destructor methods

   test_constructor();

   test_destructor();

   // Appending layers

   test_add_layer();
   check_layer_type();

   // Get methods

   test_has_methods();

   test_get_inputs();
   test_get_outputs();

   test_get_trainable_layers();
   test_get_layers_type_pointers();
   test_get_layer_pointer();

   // Assignment operators methods

// test_assignment_operator();

   // Parameters methods
/*
   test_get_parameters_number();
   test_get_parameters();
   test_get_trainable_layers_parameters_number();

   // Parameters initialization methods

   test_set_parameters_constant();
   test_set_parameters_random();

   test_forward_propagate();
   test_get_trainable_layers_parameters();





   // Parameters norm

//   test_calculate_parameters_norm();

   // Output

   test_calculate_outputs();
   test_calculate_trainable_outputs();

   // Display messages

   test_get_display();

   // Layer methods

   test_add_layer();

   // Set methods
*/
   test_set();

   test_set_names();
   test_set_number();

   test_set_pointers();

   test_set_display();

   // Layers

   test_get_layers_number();

   // Architecture

   test_inputs_outputs_number();

   test_get_architecture();

   /*
   test_set_default();

   // Parameters methods

   test_set_parameters();

   // Display messages

   test_set_display();

   // Expression methods

   test_write_expression();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   test_print();
   test_save();

   test_load();
   */

   cout << "End of neural network test case.\n";
}

// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2019 Artificial Intelligence Techniques, SL.
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
