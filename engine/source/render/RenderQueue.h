//houses/organize draw commands/calls

#pragma once
#include <vector>
namespace eng {

	class Mesh;
	class Material;
	class GraphicsAPI;

	struct RenderCommand {

		Mesh* mesh = nullptr;
		Material* material = nullptr;
	};

	class RenderQueue {

	public:
		void Submit(const RenderCommand& command);
		//execute all queued draw calls
		void Draw(GraphicsAPI& graphicsAPI);

	private:
		std::vector<RenderCommand> m_commands;
	};
}