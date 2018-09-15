#include "parser.hpp"
#include "../geometry/vec3d.hpp"
#include "../geometry/transform.hpp"
#include "../cameras/perspective.hpp"
#include "../cameras/orthographic.hpp"
#include "../samplers/multijitter.hpp"
#include "../samplers/hammerslay.hpp"
#include "../samplers/superSampler.hpp"
#include "../samplers/random.hpp"
#include "../samplers/regular.hpp"
#include "../accelerators/accelerator.hpp"
#include "../geometricObjects/objectGroup.hpp"
#include "../geometricObjects/triangle.hpp"
#include "../geometricObjects/sphere.hpp"
#include "../lights/directional.hpp"
#include "../lights/point.hpp"
#include "../materials/material.hpp"
#include "../utilities/texture.hpp"
#include "../utilities/film.hpp"
#include "../utilities/environment.hpp"
#include "../world.hpp"
#include <iostream>
#include <fstream>

using namespace rapidxml;

Parser::Parser(World * _w): w(_w), imp(new Assimp::Importer()){
  parseList = {"Film", "Camera", "Sampler", "Accelerator", "Integrator", "Materials", "Objects", "Lights", "Environment"};
}

Parser::Parser(const Parser & p): w(p.w), imp(p.imp), parseList(p.parseList){}

Parser::~Parser(){
  delete imp;
}

Parser & Parser::operator=(const Parser & p){
  w = p.w; imp = p.imp;
  return *this;
}

bool Parser::parseScene(const std::string & path){
  std::ifstream sceneFile(path);
  std::vector<char> buffer((std::istreambuf_iterator<char>(sceneFile)), std::istreambuf_iterator<char>());
  buffer.push_back('\0');
  scene.parse<0>(&buffer[0]);
  // std::cout << scene << std::endl;

  for(auto & item : parseList){
    xml_node<> * node;
    if((node = scene.first_node(item.c_str()))){
      parseSceneNode(node);
    }
    else{
      std::cout << "[Warning] <" << item << "> tag missing! Used default value.\n";
      setDefault(item);
    }
  }

  w->turbo->init();

  std::cout << "\n" << *w->film << "\n\n" << w->cam->toString() << "\n\n" << w->sampler->toString()
            << "\n\n" << *w->turbo << "\n\n" << w->env->toString() << "\n\n";

  for(auto & mat : w->materials)
    std::cout << mat.first << ": " << mat.second->toString() << "\n";

    std::cout << std::endl;

  for(auto & model : w->models)
    std::cout << "Model: " << model->toString() << "\n";

    std::cout << std::endl;

  for(auto & light : w->lights)
    std::cout << light->toString() << "\n";


  return true;
}

// bool Parser::importModel(const std::string & path, Material * mat, Transform * tr){
//   const aiScene * scene = imp->ReadFile(path,
//                                         aiProcess_CalcTangentSpace       |
//                                         aiProcess_Triangulate            |
//                                         aiProcess_JoinIdenticalVertices  |
//                                         aiProcess_SortByPType            |
//                                         aiProcess_FlipUVs);
//
//   if(!scene){
//     std::cout << "\t\t[ERROR] File reading failed, maybe invalid path?\n";
//     return false;
//   }
//
//   std::cout << "\t<Model>\n";
//
//   if(scene->HasMeshes()){
//     Vec3d p0, p1, p2, n0, n1, n2, t0, t1, t2;
//     u_int nMesh = scene->mNumMeshes;
//     ObjectGroup * og = new ObjectGroup(tr);
//     std::cout << "\t\tMesh number: " << nMesh << "\n";
//     for(u_int i = 0; i < nMesh; ++i){
//       aiMesh * mesh = scene->mMeshes[i];
//       std::cout << "\t\tMesh name: " << mesh->mName.C_Str() << "\n";
//       // if(scene->HasMaterials()){
//       //   aiMaterial * mat = scene->mMaterials[mesh->mMaterialIndex];
//       //   std::string name;
//       //   mat->Get(AI_MATKEY_NAME,name);
//       // }
//       u_int nFaces = mesh->mNumFaces;
//       std::cout << "\t\tMesh faces: " << nFaces << "\n";
//       for(u_int j = 0; j < nFaces; ++j){
//         aiFace & face = mesh->mFaces[j];
//         p0 = (tr->m->operator*(Vec4d(mesh->mVertices[face.mIndices[0]], 1.))).xyz();
//         p1 = (tr->m->operator*(Vec4d(mesh->mVertices[face.mIndices[1]], 1.))).xyz();
//         p2 = (tr->m->operator*(Vec4d(mesh->mVertices[face.mIndices[2]], 1.))).xyz();
//         if(mesh->HasTextureCoords(0)){
//           t0 = mesh->mTextureCoords[0][face.mIndices[0]];
//           t1 = mesh->mTextureCoords[0][face.mIndices[1]];
//           t2 = mesh->mTextureCoords[0][face.mIndices[2]];
//         }
//         // std::cout << "face " << j << "\n";
//         // std::cout << "p0 : " << p0 << "  t0 : " << t0 << "\n";
//         // std::cout << "p1 : " << p1 << "  t1 : " << t1 << "\n";
//         // std::cout << "p2 : " << p2 << "  t2 : " << t2 << "\n";
//         if(mesh->HasNormals()){
//           n0 = (tr->mTrInv->operator*(Vec4d(mesh->mNormals[face.mIndices[0]],0.))).xyz();
//           n1 = (tr->mTrInv->operator*(Vec4d(mesh->mNormals[face.mIndices[1]],0.))).xyz();
//           n2 = (tr->mTrInv->operator*(Vec4d(mesh->mNormals[face.mIndices[2]],0.))).xyz();
//         }
//         else{
//           n0 = n1 = n2 = (p1-p0)^(p2-p0);
//         }
//         og->addObject(new Triangle(p0, p1, p2, n0, n1, n2, t0, t1, t2, mat));
//       }
//     }
//     og->setBVertex();
//     w->addModel(og);
//     Vec3d diag = og->max - og->min;
//     std::cout << "\t\tBBox - Min: " << og->min << " - Max: " << og->max << "\n";
//     std::cout << "\t\tExtention - x: " << diag[0] << " ,y: " << diag[1] << " ,z: " << diag[2] << "\n";
//   }
//   else{
//     std::cout << "\t\t[ERROR] No meshes founded in " << path << " scene file.\n";
//     return false;
//   }
//
//   std::cout << "\t\t" << path << " succesfully loaded.\n";
//   std::cout << "\t</Model>\n";
//   return true;
// }

ObjectGroup * Parser::importModel(const std::string & path, Material * mat, Transform * tr){
  const aiScene * scene = imp->ReadFile(path,
                                        aiProcess_CalcTangentSpace       |
                                        aiProcess_Triangulate            |
                                        aiProcess_JoinIdenticalVertices  |
                                        aiProcess_SortByPType            |
                                        aiProcess_FlipUVs);

  ObjectGroup * og = new ObjectGroup(tr);

  if(!scene){
    std::cout << "[ERROR] File reading failed, maybe invalid path?\n";
    return og;
  }

  traverseModelNode(scene->mRootNode, scene, og, mat);
  // og->setBVertex();
  // Vec3d diag = og->bbox->diag();
  // std::cout << "Min: " << og->bbox->min << " - Max: " << og->bbox->max << "\n";
  // std::cout << "Extention: " << diag << "\n";
  return og;
}

bool Parser::importMesh(const aiMesh * mesh, ObjectGroup * og, Material * mat){
  Vec3d p0, p1, p2, n0, n1, n2, t0, t1, t2;
  u_int nFaces = mesh->mNumFaces;
  std::cout << "Faces #: " << nFaces << "\n";
  for(u_int j = 0; j < nFaces; ++j){
    aiFace & face = mesh->mFaces[j];
    p0 = mesh->mVertices[face.mIndices[0]];
    p1 = mesh->mVertices[face.mIndices[1]];
    p2 = mesh->mVertices[face.mIndices[2]];
    if(mesh->HasTextureCoords(0)){
      t0 = mesh->mTextureCoords[0][face.mIndices[0]];
      t1 = mesh->mTextureCoords[0][face.mIndices[1]];
      t2 = mesh->mTextureCoords[0][face.mIndices[2]];
    }
    if(mesh->HasNormals()){
      n0 = mesh->mNormals[face.mIndices[0]];
      n1 = mesh->mNormals[face.mIndices[1]];
      n2 = mesh->mNormals[face.mIndices[2]];
    }
    else{
      n0 = n1 = n2 = (p1-p0)^(p2-p0);
    }
    og->addObject(new Triangle(p0, p1, p2, n0, n1, n2, t0, t1, t2, mat));
  }
  return true;
}

bool Parser::traverseModelNode(const aiNode * node, const aiScene * scene, ObjectGroup * og, Material * mat){

  int nMeshes = node->mNumMeshes, nChildren = node->mNumChildren;
  std::string name = node->mName.C_Str();

  std::cout << "Node name: " << name;

  Material * m = mat;
  for(auto & i : w->materials){
    if(i.first == name){
      m = i.second;
    }
  }

  if(nChildren != 0){
    std::cout << " - Children #: " << nChildren << " -->\n";
    for(int i = 0; i < nChildren; ++i){
      std::cout << "Child " << i << ":\n";
      traverseModelNode(node->mChildren[i], scene, og, m);
    }
    return true;
  }
  else if(nMeshes != 0){
    std::cout << " - Meshes #: " << nMeshes << " -->\n";
    for(int i = 0; i < nMeshes; i++){
      std::cout << "Mesh " << ":\n";
      importMesh(scene->mMeshes[node->mMeshes[i]], og, m);
    }
    return true;
  }
  else
    return false;

  std::cout << "<--\n";

}

ObjectGroup * Parser::traverseObjectsNode(xml_node<> * node){
  xml_attribute<> * attr;
  xml_node<> * child;
  std::string matName, modelPath;
  std::vector<std::string> res;
  char * value;
  Transform * tr = new Transform();
  ObjectGroup * og;

  if((attr = node->first_attribute("mat")) && strcmp(attr->value(),"") != 0){
    matName = attr->value();
  }
  if(strcmp((value = node->value()),"")){
    parseTransform(value, tr);
  }

  if((attr = node->first_attribute("model")) && strcmp(attr->value(),"") != 0){
    modelPath = attr->value();
    if(matName != ""){
      og = importModel(modelPath, w->materials[matName], tr);
    }
    else{
      std::cout << "[Warning] <Group \"" << attr->name() << "\"> attribute without Material! Used default value.\n";
      og = importModel(modelPath, w->materials["default"], tr);
    }
    return og;
  }
  else if((child = node->first_node("Object"))){
    og = new ObjectGroup(tr);
    Primitive * pr = traverseObjectNode(child, matName);
    if(pr)
      og->addObject(pr);
    while((child = child->next_sibling("Object"))){
      pr = traverseObjectNode(child, matName);
      if(pr)
        og->addObject(pr);
    }
    return og;
  }
  else if((child = node->first_node("Group"))){
    og = new ObjectGroup(tr);
    og->addChild(traverseObjectsNode(child));
    while((child = child->next_sibling("Group"))){
      og->addChild(traverseObjectsNode(child));
    }
    return og;
  }

}

Primitive * Parser::traverseObjectNode(rapidxml::xml_node<> * node, const std::string & mat){
  xml_attribute<> * attr;
  std::string matName = mat;
  std::vector<std::string> res;
  char * value;

  if((attr = node->first_attribute("mat")) && strcmp(attr->value(),"") != 0){
    matName = attr->value();
  }

  if(strcmp((value = node->value()),"")){
    parseArray(value,res);
    if(res.size() < 4){
      std::cout << "[Warning] <" << node->name() << " \"center,radius\"> values size < 4. Object creation skipped.\n";
      return nullptr;
    }
    else{
      std::vector<double> n;
      for(auto & i : res){
        n.push_back(stod(i, nullptr));
      }
      if((attr = node->first_attribute("type")) && strcmp(attr->value(),"") != 0){
        if(strcmp(attr->value(),"sphere") == 0){
          if(matName != "")
            return new Sphere(Vec3d(n[0],n[1],n[2]), n[3], w->materials[matName]);
          else
            return new Sphere(Vec3d(n[0],n[1],n[2]), n[3], w->materials["default"]);
        }
      }
      else{
        std::cout << "[Warning] <" << node->name() << " \"type\"> value unknow. Object creation skipped.\n";
        return nullptr;
      }
    }
  }
  else{
    std::cout << "[Warning] <" << node->name() << " \"center,radius\"> values unknow. Object creation skipped.\n";
    return nullptr;
  }
}


bool Parser::traverseMaterialsNode(xml_node<> * node){
  xml_attribute<> * attr;
  xml_node<> * nextNode, * brdfs;
  std::vector<std::string> matsNames;
  std::string reflMapName;
  Material * mat;
  Vec3d refl;

  if((attr = node->first_attribute("name")) && strcmp(attr->value(),"") != 0){
    parseArray(attr->value(), matsNames);
  }
  else{
    std::cout << "[Warning] <Material \"" << attr->name() << "\"> attribute missing! Material creation skipped.\n";
    return false;
  }

  if((attr = node->first_attribute("refl")) && strcmp(attr->value(),"") != 0){
    std::vector<std::string> val;
    parseArray(attr->value(), val);
    if(val.size() < 2)
      refl = Vec3d(stod(val[0], nullptr));
    else if(val.size() > 2)
      refl = Vec3d(stod(val[0], nullptr),stod(val[1], nullptr),stod(val[2], nullptr));
  }
  if((attr = node->first_attribute("reflMap")) && strcmp(attr->value(),"") != 0){
    reflMapName = attr->value();
  }


  if((brdfs = node->first_node("Brdfs"))){
    if((attr = brdfs->first_attribute("type")) && strcmp(attr->value(),"") != 0){
      if(strcmp(attr->value(),"mix") == 0){

      }
      else{
        AddBrdf * mBrdf = new AddBrdf();
        traverseBrdfsNode(brdfs->first_node("Brdf"), mBrdf);
        mat = new Material(mBrdf);
      }
    }
    else{
      AddBrdf * mBrdf = new AddBrdf();
      std::cout << "[Warning] <Brdfs \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      traverseBrdfsNode(brdfs->first_node("Brdf"), mBrdf);
      mat = new Material(mBrdf);
    }
  }
  else{
    std::cout << "[Error] <Material> without <Brdfs> node.\n";
    return false;
  }

  if(refl != Vec3d())
    mat->setReflection(refl);
  else if(reflMapName != "")
    mat->setReflMap(reflMapName);

  for(auto & name : matsNames)
    w->materials[name] = mat;


  if((nextNode = node->next_sibling())){
    return traverseMaterialsNode(nextNode);
  }
  else
    return false;


}

bool Parser::traverseBrdfsNode(xml_node<> * node, MultipleBrdf * mBrdf){

  xml_node<> * nextNode;
  xml_attribute<> * attr;
  char * value;
  std::vector<std::string> res;
  Texture * txt = nullptr;

  if((attr = node->first_attribute("type")) && strcmp(attr->value(),"") != 0){
    if(strcmp(attr->value(),"emissive") == 0){
      if(strcmp((value = node->value()),"")){
        parseArray(value, res);
        if((attr = node->first_attribute("map")) && strcmp(attr->value(),"") != 0){
          if((txt = new Texture(attr->value()))){
            if(res.size() > 0){
              mBrdf->addBrdf(new Emissive(txt,stof(res[0],nullptr)));
            }
            else{
              mBrdf->addBrdf(new Emissive(txt));
            }
          }
          else{
            std::cout << "[Warning] <" << node->name() << " \"map\"> attribute error!.\n";
          }
        }
        else if(res.size() > 3){
          mBrdf->addBrdf(new Emissive(Vec3d(stod(res[0],nullptr),stod(res[1],nullptr),stod(res[2],nullptr)),stod(res[3],nullptr)));
        }
        else if(res.size() > 1 ){
          mBrdf->addBrdf(new Emissive(Vec3d(stod(res[0],nullptr)),stod(res[1],nullptr)));
        }
        else{
          std::cout << "[Warning] <" << node->name() << " \"emission,ke\"> values size != 4! Used default value.\n";
          mBrdf->addBrdf(new Emissive(Vec3d(1),1));
        }
      }
      else{
        std::cout << "[Warning] <" << node->name() << " \"emission,ke\" or \"map\"> values missing! Used default.\n";
        mBrdf->addBrdf(new Emissive(Vec3d(1),1));
      }
    }
    else if(strcmp(attr->value(),"lambert") == 0){
      if(strcmp((value = node->value()),"")){
        parseArray(value, res);
        if((attr = node->first_attribute("map")) && strcmp(attr->value(),"") != 0){
          if((txt = new Texture(attr->value()))){
            if(res.size() > 0){
              mBrdf->addBrdf(new Lambert(txt, stod(res[0],nullptr)));
            }
            else{
              mBrdf->addBrdf(new Lambert(txt));
            }
          }
          else{
            std::cout << "[Warning] <" << node->name() << " \"map\"> attribute error!.\n";
          }
        }
        else if(res.size() > 3){
          mBrdf->addBrdf(new Lambert(Vec3d(stod(res[0],nullptr),stod(res[1],nullptr),stod(res[2],nullptr)),stod(res[3],nullptr)));
        }
        else if(res.size() > 1 ){
          mBrdf->addBrdf(new Lambert(Vec3d(stod(res[0],nullptr)),stod(res[1],nullptr)));
        }
        else{
          std::cout << "[Warning] <" << node->name() << " \"albedo,kd\"> values size != 4! Used default value.\n";
          mBrdf->addBrdf(new Lambert(Vec3d(.5),1));
        }
      }
      else{
        std::cout << "[Warning] <" << node->name() << " \"albedo,kd\"> values missing! Used default.\n";
        mBrdf->addBrdf(new Lambert(Vec3d(.5),1));
      }
    }
    else if(strcmp(attr->value(),"blinn") == 0){
      if(strcmp((value = node->value()),"")){
        parseArray(value, res);
        if((attr = node->first_attribute("map")) && strcmp(attr->value(),"") != 0){
          if((txt = new Texture(attr->value()))){
            if(res.size() > 1  ){
              mBrdf->addBrdf(new Blinn(txt, stod(res[0],nullptr), stoi(res[1],nullptr, 10)));
            }
            else if(res.size() > 0 ){
              mBrdf->addBrdf(new Blinn(txt, stoi(res[0],nullptr, 10)));
            }
            else{
              std::cout << "[Warning] <" << node->name() << " \"alpha\"> value required! Used default value.\n";
              mBrdf->addBrdf(new Blinn(txt,1000));
            }
          }
          else{
            std::cout << "[Warning] <" << node->name() << " \"map\"> attribute error!.\n";
          }
        }
        else if(res.size() > 4 ){
          mBrdf->addBrdf(new Blinn(Vec3d(stod(res[0],nullptr),stod(res[1],nullptr),stod(res[2],nullptr)),stod(res[3],nullptr),stod(res[4],nullptr)));
        }
        else if(res.size() > 2 ){
          mBrdf->addBrdf(new Blinn(Vec3d(stod(res[0],nullptr)),stod(res[1],nullptr),stod(res[2],nullptr)));
        }
        else{
          std::cout << "[Warning] <" << node->name() << " \"specular,ks,alpha\"> values size != 4! Used default value.\n";
          mBrdf->addBrdf(new Blinn(Vec3d(.5),1000));
        }
      }
      else{
        std::cout << "[Warning] <" << node->name() << " \"specular,ks,alpha\"> values missing! Used default.\n";
        mBrdf->addBrdf(new Blinn(Vec3d(.5),1000));
      }
    }
    else{
      std::cout << "[Error] <Brdf \"type\"> unknow.\n";
      return false;
    }

    if((nextNode = node->next_sibling())){
      return traverseBrdfsNode(nextNode, mBrdf);
    }
    else
      return false;

  }
}

bool Parser::traverseLightsNode(rapidxml::xml_node<> * node){
  xml_attribute<> * attr;
  char * value;
  std::vector<std::string> res;

  if(strcmp((value = node->value()),"")){
    parseArray(value, res);
  }
  else{
    std::cout << "[Error] <Light> values unknow.\n";
    return false;
  }

  if((attr = node->first_attribute("type")) && strcmp(attr->value(),"") != 0){
    if(res.size() < 7){
      std::cout << "[Error] <Light> values size < 7.\n";
      return false;
    }
    else{
      if(strcmp(attr->value(),"point") == 0){
        w->addLight(new PointLight(stod(res[0],nullptr), Vec3d(stod(res[1],nullptr),stod(res[2],nullptr),stod(res[3],nullptr)), Vec3d(stod(res[4],nullptr),stod(res[5],nullptr),stod(res[6],nullptr))));
        return true;
      }
      else if(strcmp(attr->value(),"directional") == 0){
        w->addLight(new DirectionalLight(stod(res[0],nullptr), Vec3d(stod(res[1],nullptr),stod(res[2],nullptr),stod(res[3],nullptr)), Vec3d(stod(res[4],nullptr),stod(res[5],nullptr),stod(res[6],nullptr))));
        return true;
      }
      else{
        std::cout << "[Error] <Light \"type\"> unknow.\n";
        return false;
      }
    }
  }
}


void Parser::parseSceneNode(xml_node<> * node){
  std::string name = node->name();
  xml_attribute<> * attr;
  xml_node<> * child;
  char * value;
  std::vector<std::string> res;


  if(name == "Film"){
    int width, heigth;
    std::string path, fileName;

    if((attr = node->first_attribute("width")) && strcmp(attr->value(),"") != 0){
      width = std::stoi(attr->value(), nullptr, 10);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      width = 800;
    }
    if((attr = node->first_attribute("heigth")) && strcmp(attr->value(),"") != 0){
      heigth = std::stoi(attr->value(), nullptr, 10);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      heigth = 600;
    }
    if((attr = node->first_attribute("path")) && strcmp(attr->value(),"") != 0){
      path = attr->value();
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      path = "";
    }
    if(strcmp((value = node->value()),"")){
      fileName = value;
      parseString(fileName);
    }
    else{
      std::cout << "[Warning] <" << name << " \"filename\"> value missing! Used default value.\n";
      fileName = "rendering.bmp";
    }
    w->film = new Film(width, heigth, 3, path+fileName);
  }
  else if(name == "Camera"){
    double near, far;
    float fov;
    Vec3f eye, lookAt, up;
    if((attr = node->first_attribute("near")) && strcmp(attr->value(),"") != 0){
      near = std::stod(attr->value(), nullptr);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      near = 10e-5;
    }
    if((attr = node->first_attribute("far")) && strcmp(attr->value(),"") != 0){
      far = std::stod(attr->value(), nullptr);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      far = 10e5;
    }
    if((attr = node->first_attribute("fov")) && strcmp(attr->value(),"") != 0){
      fov = std::stof(attr->value(), nullptr);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      fov = 90;
    }
    if(strcmp((value = node->value()),"")){
      parseArray(value, res);
      if(res.size() < 9){
        std::cout << "[Warning] <" << name << " \"eye, lookAt, up\"> values size != 9! Used default value.\n";
        eye = Vec3f(50, 0, 0); lookAt = Vec3f(0); up = Vec3f(0, 0, 1);
      }
      else{
        eye = Vec3f(stof(res[0],nullptr),stof(res[1],nullptr),stof(res[2],nullptr));
        lookAt = Vec3f(stof(res[3],nullptr),stof(res[4],nullptr),stof(res[5],nullptr));
        up = Vec3f(stof(res[6],nullptr),stof(res[7],nullptr),stof(res[8],nullptr));
      }
    }
    else{
      std::cout << "[Warning] <" << name << " \"eye, lookAt, up\"> values missing! Used default value.\n";
      eye = Vec3f(50, 0, 0); lookAt = Vec3f(0); up = Vec3f(0, 0, 1);
    }
    if((attr = node->first_attribute("type"))){
      if(strcmp(attr->value(),"orthographic") == 0)
        w->cam = new OrthoCamera(w->film->width, w->film->heigth, near, far, fov, eye, lookAt, up);
      else
        w->cam = new PerspCamera(w->film->width, w->film->heigth, near, far, fov, eye, lookAt, up);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      w->cam = new PerspCamera(w->film->width, w->film->heigth, near, far, fov, eye, lookAt, up);
    }
  }
  else if(name == "Sampler"){
    int samples;
    if((attr = node->first_attribute("samples")) && strcmp(attr->value(),"") != 0){
      samples = std::stoi(attr->value(), nullptr, 10);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      samples = 4;
    }
    if((attr = node->first_attribute("type"))){
      if(strcmp(attr->value(),"multijitter") == 0)
        w->sampler = new MultijitterSampler(samples);
      else if(strcmp(attr->value(),"hammerslay") == 0)
        w->sampler = new HammerslaySampler(samples);
      else if(strcmp(attr->value(),"supersampler") == 0)
        w->sampler = new SuperSampler(samples);
      else if(strcmp(attr->value(),"random") == 0)
        w->sampler = new RandomSampler(samples);
      else
        w->sampler = new RegularSampler();
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      w->sampler = new MultijitterSampler(samples);
    }
  }
  else if(name == "Accelerator"){
    int gen, prim;
    if((attr = node->first_attribute("gen")) && strcmp(attr->value(),"") != 0){
      gen = std::stoi(attr->value(), nullptr, 10);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      gen = 20;
    }
    if((attr = node->first_attribute("prim")) && strcmp(attr->value(),"") != 0){
      prim = std::stoi(attr->value(), nullptr, 10);
    }
    else{
      std::cout << "[Warning] <" << name << " \"" << attr->name() << "\"> attribute missing! Used default value.\n";
      prim = 50;
    }
    w->turbo = new Accelerator(gen, prim, w);
  }
  else if(name == "Integrator"){

  }
  else if(name == "Materials"){
    w->materials["default"] = new Material(new AddBrdf(new Lambert()));
    if((child = node->first_node("Material"))){
      traverseMaterialsNode(child);
    }
    else{
      std::cout << "[Warning] No <Material> found in <" << node->name() << ">" << "\n";
    }
  }
  else if(name == "Objects"){
    if((child = node->first_node("Group"))){
      ObjectGroup * og = traverseObjectsNode(child);
      og->toWorld(nullptr);
      og->setBVertex();
      w->addModel(og);
      while((child = child->next_sibling("Group"))){
        og = traverseObjectsNode(child);
        og->toWorld(nullptr);
        og->setBVertex();
        w->addModel(og);
      }
    }
    else{
      std::cout << "[Warning] No <Group> found in <" << node->name() << ">" << "\n";
    }
  }
  else if(name == "Lights"){
    if((child = node->first_node("Light"))){
      traverseLightsNode(child);
      while((child = child->next_sibling("Light"))){
        traverseLightsNode(child);
      }
    }
  }
  else if(name == "Environment"){
    if((attr = node->first_attribute("map")) && strcmp(attr->value(),"") != 0){
      w->env = new Environment(attr->value());
    }
    else if(strcmp((value = node->value()),"")){
      parseArray(value, res);
      if(res.size() < 3){
        std::cout << "[Warning] <" << name << " \"color\"> array size != 3! Used default value.\n";
        w->env = new Environment();
      }
      else{
        w->env = new Environment(Vec3d(stod(res[0], nullptr), stod(res[1], nullptr), stod(res[2], nullptr)));
      }
    }
    else{
      std::cout << "[Warning] <" << name << " \"map\"> or color values missing! Used default value.\n";
      setDefault(name);
    }
  }


}

void Parser::setDefault(const std::string & name){
  if(name == "Film"){
    w->film = new Film(800, 600, 3);
  }
  else if(name == "Camera"){
    w->cam = new PerspCamera(w->film->width,w->film->heigth,1e-5,1e5,90,Vec3f(50,0,0), Vec3f(0,0,0), Vec3f(0,0,1));
  }
  else if(name == "Sampler"){
    w->sampler = new RegularSampler();
  }
  else if(name == "Accelerator"){
    w->turbo = new Accelerator(5, 35, w);
  }
  else if(name == "Integrator"){

  }
  else if(name == "Environment"){
    w->env = new Environment();
  }
}

void Parser::tokenize(const std::string & str, const std::string & delim, std::vector<std::string> & parts) {
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != std::string::npos)) {
      start++;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == std::string::npos)) {
      end++; // skip to end of word
    }
    if (end-start != 0) {  // just ignore zero-length strings.
      parts.push_back(std::string(str, start, end-start));
    }
  }
}

void Parser::parseArray(const std::string & s, std::vector<std::string> & parseRes){
  // char * val = strtok(s, ", \n");
  // while(val != nullptr){
  //   parseRes.push_back(val);
  //   val = strtok(nullptr, ", \n");
  // }
  std::string str = s;
  tokenize(str, ", \n", parseRes);
}


void Parser::parseTransform(const std::string & _s, Transform * tr){
  std::vector<std::string> strs;
  std::string s = _s;

  parseString(s);
  if(s[0] == '*'){
    tokenize(s, " *", strs);
    for(auto & str : strs){
      u_int pos1 = str.find('(');
      u_int n = str.find(')') - pos1 - 1;
      std::string sdatas = str.substr(pos1+1, n);
      std::vector<std::string> vdatas;
      parseArray(sdatas,vdatas);
      std::string type = str.substr(0,2);
      if( type == "tr"){
        if(vdatas.size() < 3){
          std::cout << "[ERROR] Translation datas incorrect. Creation skipped.\n";
        }
        else
        tr->operator*=(translation(stod(vdatas[0], nullptr),stod(vdatas[1], nullptr), stod(vdatas[2])));
      }
      else if(type == "sc"){
        if(vdatas.size() < 1){
          std::cout << "[ERROR] Scaling datas incorrect. Creation skipped.\n";
        }
        else if(vdatas.size() < 3)
        tr->operator*=(scaling(stod(vdatas[0], nullptr)));
        else if(vdatas.size() > 2)
        tr->operator*=(scaling(stod(vdatas[0], nullptr),stod(vdatas[1], nullptr), stod(vdatas[2])));
      }
      else if(type == "rx"){
        if(vdatas.size() < 1){
          std::cout << "[ERROR] RotationX datas incorrect. Creation skipped.\n";
        }
        else
        tr->operator*=(rotationX(stod(vdatas[0], nullptr)));
      }else if(type == "ry"){
        if(vdatas.size() < 1){
          std::cout << "[ERROR] RotationY datas incorrect. Creation skipped.\n";
        }
        else
        tr->operator*=(rotationY(stod(vdatas[0], nullptr)));
      }else if(type == "rz"){
        if(vdatas.size() < 1){
          std::cout << "[ERROR] RotationZ datas incorrect. Creation skipped.\n";
        }
        else
        tr->operator*=(rotationZ(stod(vdatas[0], nullptr)));
      }
      else
      std::cout << "[ERROR] Transform type unknow. Creation skipped.\n";
    }
  }
  else{
    parseArray(s,strs);
    if(strs.size() < 12){
      std::cout << "[ERROR] Transform datas size =! 16. Used default value.\n";
    }
    else{
      std::vector<double> n;
      for(auto & i : strs){
        n.push_back(stod(i, nullptr));
      }
      tr->operator*=(Transform(Vec3d(n[0],n[4],n[8]), Vec3d(n[1],n[5],n[9]), Vec3d(n[2],n[6],n[10]), Vec3d(n[3],n[7],n[11])));
    }
  }


}

void Parser::parseString(std::string & str){
  std::vector<std::string> res;
  tokenize(str, " \n\t\r\v", res);
  str = "";
  for(auto & i : res)
    str += i;
}


//
// bool Parser::exportMap(const std::string & path, int width, int heigth, int channels, const unsigned char * map){
//   if(SOIL_save_image(path.c_str(), SOIL_SAVE_TYPE_BMP, width, heigth, channels, map)){
//     std::cout << "\tImage succesfully saved to " << path << "\n";
//     return true;
//   }
//   else{
//     std::cout << "\t[ERROR] File saving failed.\n";
//   }
// }
