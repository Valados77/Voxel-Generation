#include "Block.h"

namespace Renderer
{
	Block::Block()
	{
		GLfloat cube[] = {
			0, 0, 0,  0.0f, 1.0f,	//0	//bottom
			0, 0, 1,  1.0f, 1.0f,	//1
			1, 0, 1,  1.0f, 0.0f,	//2
			1, 0, 0,  0.0f, 0.0f,	//3

			0,  1, 0,  0.0f, 1.0f,	//4	//top
			0,  1, 1,  0.0f, 0.0f,	//5
			1,  1, 1,  1.0f, 0.0f,	//6
			1,  1, 0,  1.0f, 1.0f,	//7
		};
	}

	void Block::generateBlock()
	{
		generateFrontSide();
		generateBackSide();
		generateLeftSide();
		generateRightSide();
		generateBottomSide();
		generateTopSide();


	}

	void Block::generateFrontSide()
	{
		m_indices.push_back(0);
		m_indices.push_back(4);
		m_indices.push_back(7);

		m_indices.push_back(7);
		m_indices.push_back(3);
		m_indices.push_back(0);
	}

	void Block::generateBackSide()
	{
		m_indices.push_back(2);
		m_indices.push_back(6);
		m_indices.push_back(5);

		m_indices.push_back(5);
		m_indices.push_back(1);
		m_indices.push_back(2);
	}

	void Block::generateLeftSide()
	{
		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(5);

		m_indices.push_back(5);
		m_indices.push_back(4);
		m_indices.push_back(0);
	}

	void Block::generateRightSide()
	{
		m_indices.push_back(2);
		m_indices.push_back(3);
		m_indices.push_back(7);

		m_indices.push_back(7);
		m_indices.push_back(6);
		m_indices.push_back(2);
	}

	void Block::generateBottomSide()
	{
		m_indices.push_back(2);
		m_indices.push_back(1);
		m_indices.push_back(0);

		m_indices.push_back(0);
		m_indices.push_back(3);
		m_indices.push_back(2);
	}

	void Block::generateTopSide()
	{
		m_indices.push_back(5);
		m_indices.push_back(6);
		m_indices.push_back(7);

		m_indices.push_back(7);
		m_indices.push_back(4);
		m_indices.push_back(5);
	}
}