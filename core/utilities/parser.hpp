#ifndef _PARSER_
#define _PARSER_

#include <string>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../../otherLibs/rapidxml-1.13/rapidxml.hpp"
#include "../../otherLibs/rapidxml-1.13/rapidxml_print.hpp"

class Material;
class Texture;
class Transform;
class World;
class ObjectGroup;
class MultipleBrdf;
class Primitive;

class Parser{
public:
  Parser(World *);
  Parser(const Parser &);
  ~Parser();

  Parser & operator=(const Parser &);

  bool parseScene(const std::string &);
  ObjectGroup * importModel(const std::string &, Material *, Transform *);
  bool importMesh(const aiMesh *, ObjectGroup *, Material *);
  bool traverseModelNode(const aiNode *, const aiScene *, ObjectGroup *, Material *);
  ObjectGroup * traverseObjectsNode(rapidxml::xml_node<> *);
  Primitive * traverseObjectNode(rapidxml::xml_node<> *, const std::string &);
  bool traverseMaterialsNode(rapidxml::xml_node<> *);
  bool traverseBrdfsNode(rapidxml::xml_node<> *, MultipleBrdf *);
  bool traverseLightsNode(rapidxml::xml_node<> *);
  void parseSceneNode(rapidxml::xml_node<> *);
  void setDefault(const std::string &);
  void tokenize(const std::string &, const std::string &, std::vector<std::string> &);
  void parseArray(const std::string &, std::vector<std::string> &);
  void parseTransform(const std::string &, Transform *);
  void parseString(std::string &);

  World * w;
  Assimp::Importer * imp;
  rapidxml::xml_document<> scene;
  std::vector<std::string> parseList;
};

#endif
