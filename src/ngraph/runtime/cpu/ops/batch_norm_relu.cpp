/*******************************************************************************
* Copyright 2017-2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "ngraph/runtime/cpu/ops/batch_norm_relu.hpp"
#include "ngraph/ops/constant.hpp"
#include "ngraph/ops/get_output_element.hpp"

ngraph::op::BatchNormRelu::BatchNormRelu(double eps,
                                 std::shared_ptr<ngraph::Node> gamma,
                                 std::shared_ptr<ngraph::Node> beta,
                                 std::shared_ptr<ngraph::Node> input)
    : RequiresTensorViewArgs("BatchNormRelu", {gamma, beta, input})
    , m_bn_input_shape(input->get_shape())
    , m_epsilon(eps)
{
    if (m_bn_input_shape.size() < 2)
    {
        throw ngraph_error("input tensor to BatchNormRelu much have tensor of atleast rank 2");
    }
    else
    {
        this->m_bn_variance_shape.push_back(input->get_shape()[1]);
        this->m_bn_mean_shape.push_back(input->get_shape()[1]);
    }

    if (m_bn_input_shape[1] == 0)
    {
        throw ngraph_error(
            "input tensor must have atleast one channel axis for batch normalization");
    }

    if ((gamma->get_shape().size() != 1) || (beta->get_shape().size() != 1))
    {
        throw ngraph_error("gamma and beta shoud have rank 1");
    }

    if (gamma->get_shape().size() != beta->get_shape().size())
    {
        throw ngraph_error("gamma and beta rank does not match");
    }

    if (gamma->get_element_type() != beta->get_element_type())
    {
        throw ngraph_error("gamma and beta element type does not match");
    }

    add_output(input->get_element_type(), m_bn_input_shape);
    add_output(input->get_element_type(), m_bn_mean_shape);
    add_output(input->get_element_type(), m_bn_variance_shape);
}

std::shared_ptr<ngraph::Node>
    ngraph::op::BatchNormRelu::copy_with_new_args(const NodeVector& new_args) const
{
    if (new_args.size() != 3)
        throw ngraph_error("Incorrect number of new arguments");
    return std::make_shared<BatchNormRelu>(m_epsilon, new_args.at(0), new_args.at(1), new_args.at(2));
}
