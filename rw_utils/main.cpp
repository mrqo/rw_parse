// rw_utils.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "rw_dff.h"
#include "rw_txd.h"
#include "rw_ide.h"

#include "rwde_window.h"
#include "rwde_mesh.h"
#include "rwde_camera.h"
#include "rwde_shader.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv)
{
	std::string models_path = "G:\\Developer2\\rw_parse\\dff\\";
	//RwDff *LODroad15 = new RwDff("C:\\Users\\MRQ\\Desktop\\rw_parse\\rw_parse\\dff\\LODroad15.dff");
	//LODroad15->openFile();
	//LODroad15->loadFile();
	//LODroad15->serialize();
	////LODroad15->printFileStructure();

	//RwDff *newramp2 = new RwDff("C:\\Users\\MRQ\\Desktop\\rw_parse\\rw_parse\\dff\\newramp2.dff");
	//newramp2->openFile();
	//newramp2->loadFile();
	//newramp2->serialize();
	////newramp2->printFileStructure();

	//RwDff *washbuild033 = new RwDff("C:\\Users\\MRQ\\Desktop\\rw_parse\\rw_parse\\dff\\washbuild033.dff");
	//washbuild033->openFile();
	//washbuild033->loadFile();
	//washbuild033->serialize();
	////washbuild033->printFileStructure();

	RwDff *dt_bowlsign = new RwDff(models_path + "dt_bowlsign.dff");
	dt_bowlsign->openFile();
	dt_bowlsign->loadFile();
	dt_bowlsign->serialize();
	//dt_bowlsign->printFileStructure();

	RwTxd *vgseland03_lvs = new RwTxd(models_path + "vgseland03_lvs.txd");
	vgseland03_lvs->openFile();
	vgseland03_lvs->loadFile();
	vgseland03_lvs->serialize();
	vgseland03_lvs->printFileStructure();

	RwIde *LAe = new RwIde(models_path + "LAe.ide");
	LAe->openFile();
	LAe->loadFile();
	LAe->serialize();

	//RwDff *player = new RwDff("C:\\Users\\HP\\Desktop\\rw-parse\\rw_parse\\dff\\player.dff");
	//player->openFile();
	//player->loadFile();
	//player->serialize();
	//player->printFileStructure();

	RWDE::Window *wnd = new RWDE::Window("RW_PARSE", SCREEN_HEIGHT, SCREEN_WIDTH);
	wnd->init();
	RWDE::Camera camera(glm::vec3(0.0f, 0.0f, -40.0f), 70.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 500.0f);
	Shader shader("./basicShader");
	Transform transform;
	RWDE::Mesh *mesh = new RWDE::Mesh(dt_bowlsign);

	transform.GetRot()->x = -2.f;

	SDL_Event e;
	bool isRunning = true;

	float counter = 0;

	while (isRunning) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		transform.GetRot()->z = counter;
		//std::cout << "transform x/y/z " << transform.GetRot()->x << " " << transform.GetRot()->y << " " << transform.GetRot()->z << std::endl;
		//wnd->clear(0.0f, 0.3f, 0.9f, 1.0f);
		wnd->clear(115.0f / 255, 132.0f / 255, 180.0f / 255, 1.0f);
		shader.Bind();
		shader.Update(transform, camera);
		
		mesh->draw();
		
		wnd->swapBuffers();
		SDL_Delay(1);
		counter += 0.001f;
	}
	system("PAUSE");
	//delete LODroad15;
	//delete newramp2;
	//delete washbuild033;
	delete dt_bowlsign;
	//delete player;
	delete LAe;
    return 0;
}

