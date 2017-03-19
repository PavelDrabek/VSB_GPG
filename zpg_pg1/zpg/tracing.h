#pragma once
#include <thread>

#define DEG2RAD( x ) ( ( x ) * static_cast<float>( M_PI / 180 ) )

/*
 * author Pavel Drabek
 * created  5.10.2016
*/
class Tracer
{
public:
	Tracer(const int width, const int height);
	void Render();
	void RenderInThread();
	void TestBackgroundRender();

	void SetScene(RTCScene *scene, std::vector<Surface*> *surfaces);
	void ShowScene();
	void ShowSceneLoop();

	static Vector3 GetRetractDir(Vector3 dir, Vector3 normal, float n1, float n2);
	static float GetFresnelR(Vector3 dir, Vector3 normal, float n1, float n2);
	static void onMouse(int event, int x, int y, int, void*);

	cv::Mat src_32fc3_img;

private:

	static const int maxDeep = 6;

	int width_; /*!< ���ka obrazu [px]. */
	int height_; /*!< V��ka obrazu [px]. */
	bool done;

	int nullDiffuseCount;
	int raysAll;
	int returnInterrupt;
	int returnFinish;
	int returnCubemap[maxDeep];

	cv::Vec3d ToColor(Vector3 v);
	Vector3 ToVector(cv::Vec3d c);

	Camera* camera;
	RTCScene* scene;
	CubeMap* cubemap;
	std::vector<Surface*> surfaces;

	Vector3 lightPos;

	Vector3 GetPoint(Ray &ray, bool stepBack = true);
	Vector3 EvalPoint(Ray &ray);
	Vector3 GetNormal(Ray &ray);
	Vector3 GetNormal(Triangle &triangle, Ray &ray);
	Vector3 GetLightPos();
	Vector3 GetLightDir(Vector3 point);
	Vector3 GetColor(Ray &ray);

	Vector3 GetCubeMapColor(Vector3 dir);

	Vector3 TraceNormal(Ray ray);
	Vector3 TraceLambert(Ray ray);
	Vector3 TracePhong(Ray ray, int deep);

	Sphere sphere = Sphere(Vector3(0.0f), 0.6f);
	Quadric quadric = Quadric(Quadric::QuadricType::Paraboloid);
	Material* defaultMaterial;

	std::thread m_thread;
};
