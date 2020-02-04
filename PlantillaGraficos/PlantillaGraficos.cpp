// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

//Declarar una vetana
GLFWwindow* window;
float posXTriangulo = 0.0f, posYTriangulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;
float rotar = 0.0f;

//CALLBACK ACTION

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{

	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_RIGHT) 
	{
		posXTriangulo += .01;
	}


	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_LEFT) 
	{
		posXTriangulo -= .01;
	}


	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_UP) 
	{
		posYTriangulo += .01;
	}

	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_DOWN) 
	{
		posYTriangulo -= .01;
	}

}


void actualizar()
{

	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);

	if (estadoDerecha == GLFW_PRESS) 
	{
		posXTriangulo += velocidadTriangulo * tiempoDiferencial;
		rotar += 100 * tiempoDiferencial;
	}

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);

	if (estadoArriba == GLFW_PRESS)
	{
		posYTriangulo += velocidadTriangulo * tiempoDiferencial;
	}

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (estadoAbajo == GLFW_PRESS)
	{
		posYTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}
	
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);

	if (estadoIzquierda == GLFW_PRESS) 
	{
		posXTriangulo -= velocidadTriangulo * tiempoDiferencial;
		rotar -= 100 * tiempoDiferencial;
	}

	tiempoAnterior = tiempoActual;

}

//la rutina del dibujo
void dibujar()
{
	glPushMatrix();

	glTranslatef(0.0, posYTriangulo, 0.0f);

	glRotatef(rotar, 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);

	//glScalef(escX,escY,escZ);

	glColor3f(0.2, 0.6, 0.1);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);
	glEnd();

	glPopMatrix();
}




int main()
{
   
	
	//si no se pudo inicializar glfw terminamos la ejecución

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Si se pudo inicial glfw, se inicia la ventana

	window = glfwCreateWindow(600,600, "ventana",NULL, NULL);

	// si no se pudo crear la ventana, terminamos la ejecución

	if (!window) 
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, se activan las funciones modernas (gpu)
	glewExperimental = true;

	//Imprimir posibles errores

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version openGL" << versionGL;

	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	//ciclo de dibujo (Draw loop)

	while (!glfwWindowShouldClose(window))
	{
		//establecer la región de dibujo
		glViewport(0, 0, 600, 600);
		//establecemos el color de borrado, valores rgba, van de 0 a 1
		glClearColor(1,.41,.9,1);
		//Borrar!  Con el borrar solo se hace el swap der buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Actualizar valores y dibujar
		actualizar();
		dibujar();
		//pa poder usar el mouse
		glfwPollEvents();
		 
		glfwSwapBuffers(window);
	}

	//Despues del ciclo de dibujo eliminamos ventana y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();

}


