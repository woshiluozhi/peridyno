/**
 * Copyright 2017-2021 Xiaowei He (xiaowei@iscas.ac.cn)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "Topology/EdgeSet.h"

#include "GLVisualModule.h"
#include "gl/CudaBuffer.h"
#include "gl/VertexArray.h"
#include "gl/Shader.h"

namespace dyno
{
	class GLWireframeVisualModule : public GLVisualModule
	{
		DECLARE_CLASS(GLWireframeVisualModule)

	public:		
		// render as lines or cylinder
		enum EEdgeMode {
			LINE = 0,
			CYLINDER = 1
		};

	public:
		GLWireframeVisualModule();
		std::string caption() override;
		void setEdgeMode(EEdgeMode mode);

		DEF_INSTANCE_IN(EdgeSet<DataType3f>, EdgeSet, "");
		DEF_VAR(float, Radius, 0.003f, "Cylinder radius");
		DEF_VAR(float, LineWidth, 1.f, "Line width");

	protected:
		virtual void paintGL(GLRenderPass mode) override;
		virtual void updateGL() override;
		virtual bool initializeGL() override;
				
	private:

		gl::Program		mShaderProgram;

		gl::VertexArray	mVAO;
		gl::CudaBuffer	mPoints;
		gl::CudaBuffer 	mEdges;
		unsigned int	mNumEdges = 0;

		EEdgeMode		mEdgeMode = EEdgeMode::CYLINDER;
	};
};