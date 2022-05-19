#include "mesh_3D.h"

bool readMesh(Mesh& mesh, const std::string& fileName) {
    // Attempt to read file.
    std::ifstream file(fileName.c_str());
    if(!file) {
        std::cerr << "Error reading file!" << std::endl;
        return false;
    }

    std::vector<FloatPoint3> V;
    std::vector<Triangle> T;

    // Fill the mesh data structure.
    std::string line;
    while ( std::getline(file, line) ) {
        std::stringstream ss;
        ss << line;
        char type;
        ss >> type;
        if(type=='v') {
            float x, y, z;
            ss >> x >> y >> z;
            V.push_back(FloatPoint3(x, y, z));
        }
        if(type=='f') {
            int a, b, c;
            ss >> a >> b >> c;
            T.push_back(Triangle(a-1, b-1, c-1));
        }
    }

    std::cout << "Successful Reading of file" << std::endl;
    std::vector< std::vector<int> > tRings(V.size());
    for (int t=0; t<int(T.size()); ++t) {
        tRings.at(T[t][0]).push_back(t);
        tRings.at(T[t][1]).push_back(t);
        tRings.at(T[t][2]).push_back(t);
    }
    std::cout << "Success computing rings" << std::endl;

    std::vector<FloatVector3> normals(V.size());
    for(int v=0; v<int(V.size()); ++v) {
        FloatVector3 n(0.f);
        for(size_t t=0; t<tRings[v].size(); ++t) {
            // std::cout << v << ',' << t << ':' << tRings[v][t] << std::endl;
            FloatPoint3 u[] = {V[T[tRings[v][t]][0]],
                               V[T[tRings[v][t]][1]],
                               V[T[tRings[v][t]][2]]};
            u[1] -= u[0];
            u[2] -= u[0];
            u[0] = u[1]^u[2];
            u[0].normalize();
            n += u[0];
        }
        n /= static_cast<float>(tRings.size());
        n.normalize();
        normals[v] = n;
    }
    std::cout << "Computing normals successful" << std::endl;

    mesh = Mesh(V,T,std::vector<Quad>(),CONSTANT_COLOR,SMOOTH_SHADING,normals);
    return true;
}
