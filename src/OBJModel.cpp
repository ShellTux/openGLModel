#include "OBJModel.hpp"

#include "types.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

OBJModel::OBJModel() {}

OBJModel::~OBJModel() {}

void OBJModel::LoadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error loading obj file: " << filename << std::endl;
    return;
  }

  std::vector<Vec3> vertices{};
  std::vector<Vec3> normals{};

  std::string line;
  char currentMtlName[1024] = "";
  while (std::getline(file, line)) {
    if (StartWith(line, "mtllib")) {
      char mtlFileName[128] = "";
      sscanf(line.c_str(), "mtllib %s", mtlFileName);
      LoadMaterialFile(mtlFileName);
    }
    if (StartWith(line, "v ")) {
      Vec3 pos{};
      sscanf(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
      vertices.push_back(pos);
    }
    if (StartWith(line, "vn ")) {
      Vec3 n{};
      sscanf(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
      normals.push_back(n);
    }
    if (StartWith(line, "usemtl")) {
      sscanf(line.c_str(), "usemtl %s", currentMtlName);
    }
    if (StartWith(line, "f ")) {
      int v1, v2, v3;
      int n1, n2, n3;

      sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3,
             &n3);

      addVertexData(v1, n1, currentMtlName, vertices, normals);
      addVertexData(v2, n2, currentMtlName, vertices, normals);
      addVertexData(v3, n3, currentMtlName, vertices, normals);
    }
  }
}

std::vector<f32> OBJModel::getVertexData() const { return mVertexData; }

i32 OBJModel::getVertexCount() const { return mVertexData.size() / 9; }

void OBJModel::LoadMaterialFile(const std::string &filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cerr << "Loading Material file failed: " << filename << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    char mtlName[128] = "";

    if (StartWith(line, "newmtl")) {
      sscanf(line.c_str(), "newmtl %s", mtlName);
      mMaterialMap[mtlName] = Color();
    }

    if (StartWith(line, "Kd")) {
      Color color = {};
      sscanf(line.c_str(), "Kd %f %f %f", &color.r, &color.g, &color.b);
      mMaterialMap[mtlName] = color;
    }
  }
}

bool OBJModel::StartWith(const std::string &line, const char *text) {
  usize textLength = strlen(text);

  if (line.size() < textLength) {
    return false;
  }

  for (usize i = 0; i < textLength; ++i) {
    if (line[i] == text[i]) {
      continue;
    }

    return false;
  }

  return true;
}

void OBJModel::addVertexData(const i32 vIdx, const i32 nIdx,
                             const char *const mtl,
                             const std::vector<Vec3> &vertices,
                             const std::vector<Vec3> &normals) {
  Color c = mMaterialMap.at(mtl);
  Vec3 p = vertices[vIdx - 1];
  Vec3 n = normals[nIdx - 1];

  mVertexData.push_back(p.x);
  mVertexData.push_back(p.y);
  mVertexData.push_back(p.z);
  mVertexData.push_back(c.r);
  mVertexData.push_back(c.g);
  mVertexData.push_back(c.b);
  mVertexData.push_back(n.x);
  mVertexData.push_back(n.y);
  mVertexData.push_back(n.z);
}
