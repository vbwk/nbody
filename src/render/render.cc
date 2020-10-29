#include <stdio.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include <bx/math.h>
#include <fstream>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 800
#define N 100
#define DT 0.015

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height); 
}

struct PosColorVertex 
{
	/* positions in 3D space */
	float m_x; 
	float m_y; 
	float m_z; 

	/* color value */ 
	uint32_t m_abgr; 

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 
				3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 
				4, bgfx::AttribType::Uint8, true)
			.end(); 
	}; 
	
	static bgfx::VertexLayout ms_decl; 
}; 

bgfx::VertexLayout PosColorVertex::ms_decl; 

static PosColorVertex tetrahVertices[] = 
{
	{0.942809f, 0.0f, -0.333333f, 0xffff0000},
	{-0.471405f, 0.666667f, -0.333333f, 0xff00ff00},
	{-0.471405f, -0.666667f, -0.333333f, 0xff0000ff},
	{0.0f, 0.0f, 1.0f, 0xff00ffff},
}; 	

static const uint16_t tetrahTriList[] = 
{
	0, 1, 2,
	0, 3, 1,
	1, 3, 2,
	0, 2, 3,
}; 

bgfx::ShaderHandle loadShader(const char* _name)
{
	char* data = new char[2048]; 
	std::ifstream file; 
	size_t fileSize; 
	file.open(_name); 

	if(file.is_open()) 
	{
		file.seekg(0, std::ios::end); 
		fileSize = file.tellg(); 
		file.seekg(0, std::ios::beg); 
		file.read(data, fileSize); 
		file.close();
	}

	const bgfx::Memory* mem = bgfx::copy(data, fileSize+1);
	mem->data[mem->size-1] = '\0'; 
	bgfx::ShaderHandle handle = bgfx::createShader(mem); 
	bgfx::setName(handle, _name); 
	return handle; 
}

bgfx::VertexBufferHandle m_vbh, t_vbh; 
bgfx::IndexBufferHandle m_ibh, t_ibh; 

bgfx::ProgramHandle m_program, t_program; 

int main()
{	
	/* create glfw window */ 

	glfwInit(); 
	GLFWwindow* window = glfwCreateWindow(
		WIDTH, HEIGHT, "lorenz", NULL, NULL); 

	if (window == NULL)
	{
		perror("glfw error"); 
		exit(0); 
	}

	glfwMakeContextCurrent(window); 
	glfwSetFramebufferSizeCallback(
		window, framebuffer_size_callback); 

	/* initialize bgfx */ 

	bgfx::PlatformData pd; 
	pd.ndt = glfwGetX11Display(); 
	pd.nwh = (void*)(uintptr_t)glfwGetX11Window(window); 
	bgfx::setPlatformData(pd); 

	bgfx::renderFrame(); 

	bgfx::init(); 

	/* initialize vertex and index buffer handle */ 
	PosColorVertex::init(); 

	t_vbh = bgfx::createVertexBuffer(
			bgfx::makeRef(tetrahVertices, sizeof(tetrahVertices)), 
			PosColorVertex::ms_decl
			); 

	t_ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(tetrahTriList, sizeof(tetrahTriList))
			); 

	/* initialize program handle */ 
	bgfx::ShaderHandle vsh = loadShader("vertex.bin"); 
	bgfx::ShaderHandle fsh = loadShader("fragment.bin"); 
	t_program = bgfx::createProgram(vsh, fsh, true); 
	
	/* reset window */
	bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC); 

	/* enable debug text */ 
	bgfx::setDebug(BGFX_DEBUG_TEXT); 

	/* set view rectangle for 0th view */ 
	bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT)); 

	/* clear the view rectangle */ 
	bgfx::setViewClear(
			0, 
			BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
			0x222222FF,
			1.0f, 
			0); 

	/* set empty primitive on screen */ 
	bgfx::touch(0);

	/* render loop */ 

	float time = 0.0f; 
	
	while(!glfwWindowShouldClose(window))
	{
		processInput(window); 

		/* define where camera is and what looking at */ 
		const bx::Vec3 at  = { 0.0f, 0.0f, 0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, 80.0f };

		/* set view and projection matrix */ 
		float view[16];
		bx::mtxLookAt(view, eye, at);

		float proj[16];
		bx::mtxProj(proj,
			    60.0f,
			    float(WIDTH)/float(HEIGHT),
			    0.1f, 
			    100.0f,
			    bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(0, view, proj);

		/* Set view 0 default viewport */ 
		bgfx::setViewRect(0, 0, 0, WIDTH, HEIGHT);

		/* render cubes */ 

		for (int yy = 0; yy < N; yy++)
		{
			float mtx[16]; 

			bx::mtxRotateXY(mtx, 
					time + yy * 0.25f, 
					time + yy * 0.35f); 

			mtx[12] = -15.0f + float(yy) * 3.0f; 
			mtx[13] = -15.0f + float(yy) * 3.0f; 
			mtx[14] = 0.0f;  

#if 0
			mtx[12] = x[yy]; 
			mtx[13] = y[yy]; 
			mtx[14] = z[yy]; 
#endif

			/* set model matrix for rendering */ 
			bgfx::setTransform(mtx); 

			/* set vertex and index buffer */ 
			bgfx::setVertexBuffer(0, t_vbh); 
			bgfx::setIndexBuffer(t_ibh); 

			/* submit primitive for rendering to view 0 */ 
			bgfx::submit(0, t_program); 
		}

		glfwPollEvents(); 

		/* advance to next frame */ 
		bgfx::frame(); 
		time += 0.01f; 
	}

	bgfx::shutdown(); 
	glfwDestroyWindow(window); 
	glfwTerminate(); 
	return 0; 
}

