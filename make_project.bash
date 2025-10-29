echo -n "Project name: "
read projectName 


# 
#	Template Code
#

cmakeEngineProjectCode="
cmake_minimum_required(VERSION 3.20.0)
project(Project)
add_subdirectory(${projectName})"

cmakeProjectCode="
cmake_minimum_required(VERSION 3.20.0)

project(${projectName})

file(GLOB sources \${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${projectName} \${sources})
target_link_libraries(${projectName} Engine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"${PROJECT_SOURCE_DIR}\")"

cppHeaderCode="
#include <Engine.hpp>

class ${projectName} : public Application
{
    Mesh cubeMesh;
    Material basicMaterial;
    void OnStart() override;
    void OnUpdate(float dt) override;
    void OnEnd() override;
};"

cppSourceCode="
#include \"${projectName}.hpp\"

using namespace glm;

void ${projectName}::OnStart()
{
    cubeMesh = Mesh::CubeMesh();
    basicMesh.shader = BASIC_3D_SHADER;
}

void ${projectName}::OnUpdate(float dt)
{
	mRenderer->BeginFrame(vec4(0.5), mWindow->GetSize());
    mRenderer->Submit(cubeMesh, basicMaterial, Transform());
    mRenderer->EndFrame();
}

void ${projectName}::OnEnd()
{
}

CREATE_APPLICATION(${projectName})"


projectPath=Project/${projectName}

mkdir ${projectPath}

echo "${cmakeEngineProjectCode}" > ${projectPath}/../CMakeLists.txt
echo "${cmakeProjectCode}" > ${projectPath}/CMakeLists.txt

echo "${cppHeaderCode}" > ${projectPath}/${projectName}.hpp
echo "${cppSourceCode}" > ${projectPath}/${projectName}.cpp


