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

#pragma once

#include "ngraph/node.hpp"
#include "ngraph/op/op.hpp"
#include "ngraph/op/util/requires_tensor_view_args.hpp"
#include "ngraph/op/util/unary_elementwise_arithmetic.hpp"
#include "ngraph/util.hpp"

#include <memory>

namespace ngraph
{
    namespace op
    {
        /// \brief Elementwise Relu operation.
        ///
        class Relu : public ngraph::op::util::UnaryElementwiseArithmetic
        {
        public:
            /// \brief Constructs a Relu operation.
            ///
            /// \param arg Node that produces the input tensor.
            Relu(std::shared_ptr<ngraph::Node> arg);
            Relu(const Relu&, const NodeVector& new_args);

            virtual void generate_adjoints(autodiff::Adjoints& adjoints,
                                           const std::shared_ptr<Node>& delta) override;
        };

        /// \brief Elementwise ReluBackprop operation.
        ///
        class ReluBackprop : public ngraph::op::util::RequiresTensorViewArgs
        {
        public:
            /// \brief Constructs a ReluBackprop operation.
            ///
            /// \param arg Node that produces the relu forward input tensor.
            ReluBackprop(std::shared_ptr<ngraph::Node> arg, std::shared_ptr<ngraph::Node> delta);
            ReluBackprop(const ReluBackprop&, const NodeVector& new_args);
        };
    }
}
