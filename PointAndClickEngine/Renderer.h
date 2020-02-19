#pragma once

class Renderer
{
};

class IRenderable {
public:
	virtual ~IRenderable();
	virtual void Render() = 0;
};

