// #ifndef _BUILD_FUNCTIONS_
// #define _BUILD_FUNCTIONS_
//
// #include "../world.hpp"
// #include "../cameras/orthographic.hpp"
// #include "../cameras/perspective.hpp"
// #include "../samplers/random.hpp"
// #include "../geometricObjects/objectGroup.hpp"
// #include "../geometricObjects/plane.hpp"
// #include "../geometricObjects/sphere.hpp"
// #include "../geometricObjects/disk.hpp"
// #include "../geometricObjects/ring.hpp"
// #include "../geometricObjects/triangle.hpp"
// #include "../geometricObjects/box.hpp"
// #include "../lights/directional.hpp"
// #include "../lights/point.hpp"
// #include "../utilities/constants.hpp"
// #include "../utilities/math.hpp"
// #include "../utilities/parser.hpp"
// #include "../utilities/film.hpp"
//
//
// using namespace std;
//
// // void saturn(World * w){
// //
// //   w->bgColor = BLACK;
// //
// //   w->cam = new PerspCamera(1280,720,1e-5,1e5,30, Vec3f(10, 0, -.4), Vec3f(0,0,-.4), Vec3f(0,0,1));
// //
// //   w->addLight(new DirectionalLight(1., WHITE, Vec3d(-.5,-.5,-1)));
// //
// //   Material * mat1 = new Material(to01(186, 140, 80));
// //   Material * mat2 = new Material(to01(124, 99, 57));
// //   Material * mat3 = new Material(to01(149, 125, 84));
// //   Material * mat4 = new Material(to01(180, 157, 118));
// //   Material * mat5 = new Material(to01(209, 191, 161));
// //
// //   ObjectGroup * og = new ObjectGroup(new Transform());
// //
// //   og->addObject(new Sphere(Vec3d(0), 2, mat1));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 2.4, 2.3, mat2));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 2.65, 2.43, mat3));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 3.2, 2.7, mat4));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 4, 3.3, mat5));
// //
// //   w->addModel(og);
// // }
// //
// // void saturnOrtho(World * w){
// //
// //   w->bgColor = BLACK;
// //
// //   w->cam = new OrthoCamera(1280,720,1e-5,1e5,179, Vec3f(10, 0, 0), Vec3f(0,0,0), Vec3f(0,0,1));
// //
// //   // w->cam->samples = 1;
// //
// //   w->addLight(new DirectionalLight(2., WHITE, Vec3d(-.5,-.5,-1)));
// //
// //   Material * mat1 = new Material(to01(186, 140, 80));
// //   Material * mat2 = new Material(to01(124, 99, 57));
// //   Material * mat3 = new Material(to01(149, 125, 84));
// //   Material * mat4 = new Material(to01(180, 157, 118));
// //   Material * mat5 = new Material(to01(209, 191, 161));
// //
// //   ObjectGroup * og = new ObjectGroup(new Transform());
// //
// //   og->addObject(new Sphere(Vec3d(0), 2, mat1));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 2.4, 2.3, mat2));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 2.65, 2.43, mat3));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 3.2, 2.7, mat4));
// //   og->addObject(new Ring(Vec3d(0), Vec3d(.5,.5,1), 4, 3.3, mat5));
// //
// //   w->addModel(og);
// //
// // }
// //
// // void balls(World * w){
// //
// //   w->bgColor = BLACK;
// //
// //   w->cam = new PerspCamera(1280,720,.0001,1000, 14, Vec3f(300,0,0), Vec3f(0), Vec3f(0,0,1));
// //
// //   w->addLight(new DirectionalLight(2., WHITE, Vec3d(-1, 0, 0)));
// //
// //   // w->cam->samples = 6;
// //
// //   srand48(100);
// //
// //   ObjectGroup * og = new ObjectGroup(new Transform());
// //
// //   for(int i = 0; i < 10; i++){
// //     float y = 12*i*cos(i*PI*.25);
// //     float z = 6*i*sin(i*PI*.25);
// //     float x = i*i;
// //     og->addObject(new Sphere(Vec3d(x,y,-z), drand48()*2 + 4, new Material(Vec3d(drand48(),drand48(),drand48()))));
// //   }
// //
// //   w->addModel(og);
// // }
//
// void r2_bb(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(1920,1080,1e-5,1e5,20,Vec3f(80,80,25), Vec3f(0,0,15), Vec3f(0,0,1));
//
//
//   // w->cam->samples = 1;
//
//   // w->addLight(new PointLight(25, WHITE, Vec3d(0, 0, 30)));
//   w->addLight(new PointLight(3, WHITE, Vec3d(-30, 0, 1)));
//   w->addLight(new PointLight(3, WHITE, Vec3d(0, -25, 1)));
//   w->addLight(new PointLight(50, WHITE, Vec3d(0, 0, 67)));
//   // w->addLight(new DirectionalLight(3., WHITE, Vec3d(-.5,-.45,-.1)));
//   // w->addLight(new DirectionalLight(1, WHITE, Vec3d(0,-1,0)));
//
//   Texture * diffuse_corner = new Texture("../assets/txt/metalwall.jpg");
//
//
//   Material * mat1 = new Material(new AddBrdf(new Lambert(diffuse_corner)));
//   w->addMaterial(mat1);
//
//   Texture * diffuse_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Diffuse.dds");
//   Texture * emissive_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Illumination.dds");
//   Texture * specular_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Specular.dds");
//   Texture * diffuse_bb = new Texture("../assets/Star_Pack/Maps/Body_Diffuse.dds");
//   Texture * emissive_bb = new Texture("../assets/Star_Pack/Maps/Body_Illumination.dds");
//   Texture * specular_bb = new Texture("../assets/Star_Pack/Maps/Body_Specular.dds");
//
//   AddBrdf * brdf_r2 = new AddBrdf();
//   brdf_r2->addBrdf(new Emissive(emissive_r2));
//   brdf_r2->addBrdf(new Lambert(diffuse_r2));
//   brdf_r2->addBrdf(new Blinn(specular_r2, 70));
//   Material * mat2 = new Material(brdf_r2);
//   w->addMaterial(mat2);
//   AddBrdf * brdf_bb = new AddBrdf();
//   brdf_bb->addBrdf(new Emissive(emissive_bb));
//   brdf_bb->addBrdf(new Lambert(diffuse_bb));
//   brdf_bb->addBrdf(new Blinn(specular_bb, 70));
//   Material * mat3 = new Material(brdf_bb);
//   w->addMaterial(mat3);
//
//   w->parser->importModel("../assets/corner.obj", mat1, new Transform(scaling(6)));
//   w->parser->importModel("../assets/Star_Pack/R2-Unit.obj", mat2, new Transform(translation(-35,0,0)*rotationZ(90)*rotationX(90)*scaling(.22)));
//   w->parser->importModel("../assets/Star_Pack/BB-Unit.obj", mat3, new Transform(translation(0,-35,11.2)*rotationZ(180)*rotationX(90)*scaling(.18)));
//
//
// }
//
// void provaMesh(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(800,600,1e-5,1e5,40,Vec3f(80,-80,15), Vec3f(0,0,15), Vec3f(0,0,1));
//
//   // w->cam->samples = 1;
//
//   // w->addLight(new PointLight(25, WHITE, Vec3d(0, 0, 30)));
//   // w->addLight(new DirectionalLight(1., WHITE, Vec3d(-1,-.5,-.2)));
//   w->addLight(new DirectionalLight(3, WHITE, Vec3d(-1,-1,-.5)));
//
//
//   Texture * diffuse_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Diffuse.dds");
//
//   Material * mat1 = new Material(new AddBrdf(new Lambert(to01(159, 142, 104))));
//   w->addMaterial(mat1);
//   AddBrdf * brdf_r2 = new AddBrdf();
//   brdf_r2->addBrdf(new Lambert(diffuse_r2));
//   // brdf_r2->addBrdf(new Blinn(WHITE, .4, 70));
//   Material * mat2 = new Material(brdf_r2);
//   w->addMaterial(mat2);
//   AddBrdf * brdf_bb = new AddBrdf();
//   brdf_bb->addBrdf(new Lambert(MATTE_ORANGE));
//   brdf_bb->addBrdf(new Blinn(WHITE, .2, 70));
//   Material * mat3 = new Material(brdf_bb);
//   w->addMaterial(mat3);
//
//   w->parser->importModel("../assets/corner.obj", mat1, new Transform(scaling(6)));
//   w->parser->importModel("../assets/Star_Pack/R2-Unit.obj", mat2, new Transform(rotationZ(90)*rotationX(90)*scaling(.22)));
//   // w->parser->importModel("../assets/Star_Pack/BB-Unit.obj", mat3, new Transform(translation(0,-35,11.2)*rotationZ(180)*rotationX(90)*scaling(.18)));
//
//   // ObjectGroup * og = new ObjectGroup(new Transform(translation(0,0,10)*scaling(10)));
//   // og->addObject(new Sphere(Vec3d(0,-1,0), .5, new Material(MATTE_RED)));
//   // og->addObject(new Sphere(Vec3d(0,1,0), .5, new Material(MATTE_GREEN)));
//   // og->addObject(new Sphere(Vec3d(0,0,1), .5, new Material(MATTE_BLUE)));
//   // og->addObject(new Sphere(Vec3d(0,0,-1), .5, new Material(MATTE_MAGENTA)));
//   // og->toWorld();
//   // og->setBVertex();
//   // w->addModel(og);
//
//
// }
//
// void cube_text(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(800,600,1e-5,1e5,20,Vec3f(80,80,35), Vec3f(0,0,15), Vec3f(0,0,1));
//
//   // w->cam->samples = 1;
//
//   w->addLight(new PointLight(25, WHITE, Vec3d(15, 15, 20)));
//   // w->addLight(new DirectionalLight(1., WHITE, Vec3d(-1,-.5,-.2)));
//   // w->addLight(new DirectionalLight(3, WHITE, Vec3d(-1,-1,-.5)));
//
//
//   Texture * kd = new Texture("../assets/txt/metal.bmp");
//   // kd->save("../assets/provaa.bmp");
//
//   Material * mat1 = new Material(new AddBrdf(new Lambert(kd)));
//   w->addMaterial(mat1);
//   Material * mat2 = new Material(new AddBrdf(new Lambert(to01(159, 142, 104))));
//   w->addMaterial(mat2);
//   // AddBrdf * brdf_r2 = new AddBrdf();
//   // brdf_r2->addBrdf(new Lambert(diffuse_r2));
//   // brdf_r2->addBrdf(new Blinn(WHITE, .4, 70));
//   // Material * mat2 = new Material(brdf_r2);
//   // w->addMaterial(mat2);
//   // AddBrdf * brdf_bb = new AddBrdf();
//   // brdf_bb->addBrdf(new Lambert(MATTE_ORANGE));
//   // brdf_bb->addBrdf(new Blinn(WHITE, .2, 70));
//   // Material * mat3 = new Material(brdf_bb);
//   // w->addMaterial(mat3);
//
//   w->parser->importModel("../assets/corner.obj", mat2, new Transform(scaling(6)));
//   w->parser->importModel("../assets/cube_tex.obj", mat1, new Transform(translation(0,0,10)*scaling(10)));
//
// }
//
// void prova1(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(800,600,1e-5,1e5,20,Vec3f(50,50,20), Vec3f(0,0,0), Vec3f(0,0,1));
//
//   w->addLight(new DirectionalLight(3., WHITE, Vec3d(-1,-1,-1)));
//   w->addLight(new PointLight(5, WHITE, Vec3d(0, 0, 3)));
//
//   Texture * kd = new Texture("../assets/cb_t/cube.bmp");
//
//   Material * mat1 = new Material(new AddBrdf(new Lambert(kd)));
//   Material * mat2 = new Material(new AddBrdf(new Lambert(to01(145, 217, 101))));
//   w->addMaterial(mat1);
//   w->addMaterial(mat2);
//
//   w->parser->importModel("../assets/cb_t/cube.obj", mat1, new Transform(translation(0,0,1)*scaling(2)));
//   w->parser->importModel("../assets/corner.obj", mat2, new Transform(scaling(3)));
//
// }
//
// void prova2(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(800,600,1e-5,1e5,20,Vec3f(50,50,20), Vec3f(0,0,0), Vec3f(0,0,1));
//
//   w->addLight(new DirectionalLight(3., WHITE, Vec3d(-1,-1,-1)));
//   w->addLight(new PointLight(5, WHITE, Vec3d(0, 0, 3)));
//
//   Material * mat1 = new Material(new AddBrdf(new Lambert(RED)));
//   Material * mat2 = new Material(new AddBrdf(new Lambert(to01(145, 217, 101))));
//   w->addMaterial(mat1);
//   w->addMaterial(mat2);
//
//   w->parser->importModel("../assets/Star_Pack/BB-Unit.obj", mat1, new Transform(translation(0,0,10)*scaling(2)));
//   w->parser->importModel("../assets/corner.obj", mat2, new Transform(scaling(3)));
//
// }
//
//
// void xwing(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(7680,4320,1e-5,1e5,40,Vec3f(90,-10,0), Vec3f(0,-10,0), Vec3f(0,0,1));
//
//
//   // w->cam->samples = 1;
//
//   // w->addLight(new PointLight(25, WHITE, Vec3d(0, 0, 30)));
//   // w->addLight(new PointLight(3, WHITE, Vec3d(-30, 0, 1)));
//   // w->addLight(new PointLight(3, WHITE, Vec3d(0, -25, 1)));
//   // w->addLight(new PointLight(50, WHITE, Vec3d(0, 0, 67)));
//   // w->addLight(new DirectionalLight(3., WHITE, Vec3d(-.5,-.45,-.1)));
//   w->addLight(new DirectionalLight(3, WHITE, Vec3d(-1,0,-1)));
//
//   Texture * diffuse_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Diffuse.dds");
//   Texture * emissive_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Illumination.dds");
//   Texture * specular_r2 = new Texture("../assets/Star_Pack/Maps/R2D2_Specular.dds");
//   Texture * diffuse_xw = new Texture("../assets/Star_Pack/Maps/XWing_Diffuse_01.dds");
//   Texture * emissive_xw = new Texture("../assets/Star_Pack/Maps/XWing_Illumination_01.dds");
//   Texture * specular_xw = new Texture("../assets/Star_Pack/Maps/XWing_Specular_01.dds");
//   Texture * diffuse_earth = new Texture("../assets/earth/earth_cloudy_diffuse.jpg");
//   Texture * specular_earth = new Texture("../assets/earth/earth_spec.jpg");
//   Texture * diffuse_moon = new Texture("../assets/moon/moonmap8k.bmp");
//
//   AddBrdf * brdf_r2 = new AddBrdf();
//   brdf_r2->addBrdf(new Emissive(emissive_r2));
//   brdf_r2->addBrdf(new Lambert(diffuse_r2));
//   brdf_r2->addBrdf(new Blinn(specular_r2, 70));
//   Material * mat1 = new Material(brdf_r2);
//   w->addMaterial(mat1);
//   AddBrdf * brdf_xw = new AddBrdf();
//   brdf_xw->addBrdf(new Emissive(emissive_xw));
//   brdf_xw->addBrdf(new Lambert(diffuse_xw));
//   brdf_xw->addBrdf(new Blinn(specular_xw, 1000));
//   Material * mat4 = new Material(brdf_xw);
//   w->addMaterial(mat4);
//   AddBrdf * brdf_earth = new AddBrdf();
//   brdf_earth->addBrdf(new Lambert(diffuse_earth));
//   brdf_earth->addBrdf(new Blinn(specular_earth, 200));
//   Material * mat2 = new Material(brdf_earth);
//   w->addMaterial(mat2);
//   AddBrdf * brdf_moon = new AddBrdf();
//   brdf_moon->addBrdf(new Lambert(diffuse_moon));
//   Material * mat3 = new Material(brdf_moon);
//   w->addMaterial(mat3);
//
//   w->parser->importModel("../assets/Star_Pack/R2-Unit.obj", mat1, new Transform(translation(-2.8,1,-.8)*rotationZ(40)*rotationY(50)*rotationX(90)*scaling(.05)));
//   w->parser->importModel("../assets/Star_Pack/X-Fighter.obj", mat4, new Transform(translation(0,0,0)*rotationZ(40)*rotationY(50)*rotationX(90)*scaling(.05)));
//   w->parser->importModel("../assets/earth/earth.obj", mat2, new Transform(translation(-450,-200,-100)*rotationZ(0)*rotationY(0)*rotationX(75)*scaling(1)));
//   w->parser->importModel("../assets/moon/moon.obj", mat3, new Transform(translation(-380,-140,-75)*rotationZ(0)*rotationY(0)*rotationX(75)*scaling(.25)));
//
//
//
// }
//
// void lightsabers(World * w){
//
//   w->bgColor = BLACK;
//
//   w->cam = new PerspCamera(7680,4320,1e-5,1e5,50,Vec3f(25,0,25), Vec3f(0,0,0), Vec3f(0,0,1));
//
//
//   // w->cam->samples = 1;
//
//   w->addLight(new PointLight(8, RED, Vec3d(-11, 0, 1)));
//   w->addLight(new PointLight(6, GREEN, Vec3d(-11, -9, 1)));
//   w->addLight(new PointLight(10, Vec3d(0,.4,1), Vec3d(-11, 8.5, 1)));
//   w->addLight(new PointLight(25, WHITE, Vec3d(10, 0, 10)));
//   // w->addLight(new DirectionalLight(3., WHITE, Vec3d(-.5,-.45,-.1)));
//   // w->addLight(new DirectionalLight(3, WHITE, Vec3d(-1,0,-1)));
//
//   Texture * diffuse_obi = new Texture("../assets/Star_Pack/Maps/Light_Sabers_Obi_Diffuse.dds");
//   Texture * specular_obi = new Texture("../assets/Star_Pack/Maps/Light_Sabers_Obi_Specular.dds");
//   Texture * diffuse_luke = new Texture("../assets/Star_Pack/Maps/Light_Sabers_Luke_01_Diffuse.dds");
//   Texture * specular_luke = new Texture("../assets/Star_Pack/Maps/Light_Sabers_Luke_01_Specular.dds");
//   Texture * diffuse_vad = new Texture("../assets/Star_Pack/Maps/Light_Sabers_Darth_Diffuse.dds");
//   Texture * specular_vad = new Texture("../assets/Star_Pack/Maps/Light_Sabers_Darth_Specular.dds");
//   Texture * diffuse_floor = new Texture("../assets/txt/rustmetal.jpg");
//
//   AddBrdf * brdf_obi = new AddBrdf();
//   brdf_obi->addBrdf(new Lambert(diffuse_obi));
//   brdf_obi->addBrdf(new Blinn(specular_obi, 500));
//   Material * mat1 = new Material(brdf_obi);
//   w->addMaterial(mat1);
//   AddBrdf * brdf_luke = new AddBrdf();
//   brdf_luke->addBrdf(new Lambert(diffuse_luke));
//   brdf_luke->addBrdf(new Blinn(specular_luke, 500));
//   Material * mat4 = new Material(brdf_luke);
//   w->addMaterial(mat4);
//   AddBrdf * brdf_vad = new AddBrdf();
//   brdf_vad->addBrdf(new Lambert(diffuse_vad));
//   brdf_vad->addBrdf(new Blinn(specular_vad, 500));
//   Material * mat2 = new Material(brdf_vad);
//   w->addMaterial(mat2);
//   AddBrdf * brdf_floor = new AddBrdf();
//   brdf_floor->addBrdf(new Lambert(diffuse_floor));
//   brdf_floor->addBrdf(new Blinn(Vec3d(1.), .3, 50));
//   Material * mat3 = new Material(brdf_floor);
//   w->addMaterial(mat3);
//
//   w->parser->importModel("../assets/Star_Pack/Obi_Saber.obj", mat1, new Transform(translation(-2,8,0)*rotationZ(180)*rotationY(0)*rotationX(45)*scaling(.05)));
//   w->parser->importModel("../assets/Star_Pack/Darth_Saber.obj", mat2, new Transform(translation(0,0,0)*rotationZ(180)*rotationY(0)*rotationX(45)*scaling(.05)));
//   w->parser->importModel("../assets/Star_Pack/Luke_Saber.obj", mat4, new Transform(translation(0,-3,0)*rotationZ(0)*rotationY(0)*rotationX(0)*scaling(.04)));
//   w->parser->importModel("../assets/floor.obj", mat3, new Transform(translation(0,0,-1.5)*scaling(3.5)));
//
//
//
// }
//
// #endif
