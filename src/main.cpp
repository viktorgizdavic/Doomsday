#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <LightStructs.h>
#include <iostream>
#include <Game.h>

#include <Room.h>
#include <Cube.h>
#include <LightCube.h>
#include <crosshair.h>
#include <ModelObject.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// camera

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



struct ProgramState {
    glm::vec3 clearColor = glm::vec3(0);
    bool ImGuiEnabled = false;
    Camera camera;
    Game game;
    bool CameraMouseMovementUpdateEnabled = true;
    glm::vec3 backpackPosition = glm::vec3(0.0f, -10.0f, 0.0f);
    float backpackScale = 1.0f;
    PointLight pointLight;
    ProgramState()
            : camera(glm::vec3(0.0f, -10.0f, 3.0f)),
              game(Game())
            {}

    void SaveToFile(std::string filename);

    void LoadFromFile(std::string filename);
};

void ProgramState::SaveToFile(std::string filename) {
    std::ofstream out(filename);
    out << clearColor.r << '\n'
        << clearColor.g << '\n'
        << clearColor.b << '\n'
        << ImGuiEnabled << '\n'
        << camera.Position.x << '\n'
        << camera.Position.y << '\n'
        << camera.Position.z << '\n'
        << camera.Front.x << '\n'
        << camera.Front.y << '\n'
        << camera.Front.z << '\n';
}

void ProgramState::LoadFromFile(std::string filename) {
    std::ifstream in(filename);
    if (in) {
        in >> clearColor.r
           >> clearColor.g
           >> clearColor.b
           >> ImGuiEnabled
           >> camera.Position.x
           >> camera.Position.y
           >> camera.Position.z
           >> camera.Front.x
           >> camera.Front.y
           >> camera.Front.z;
    }
}

ProgramState *programState;

void DrawImGui(ProgramState *programState);

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    programState = new ProgramState;
    programState->LoadFromFile("resources/program_state.txt");
    if (programState->ImGuiEnabled) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    // Init Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;



    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


    glm::vec3 scaling(xScaling1,yScaling1,zScaling1);
    glm::vec3 translated(xTranslate1,yTranslate1,zTranslate1);

    //init directional light
    DirLight dirLight;
    dirLight.direction=glm::vec3(0.0f,0.0f,-1.0f);
    dirLight.ambient=glm::vec3 (0.05f, 0.05f, 0.05f);
    dirLight.diffuse=glm::vec3(0.0f, 0.0f, 0.0f);
    dirLight.specular=glm::vec3(0.0f, 0.0f, 0.0f);


    //init point lights
    int pointLightCount=5;
    std::vector<glm::vec3> pointLightPositions = {
            scaling*(glm::vec3(30.0f,0.0f,-30.0f)+translated),
            scaling*(glm::vec3(0.0f,15.0f,-30.0f+(60.0f*1/3))+translated),
            scaling*(glm::vec3(-60.0f*1/3,15.0f,-30.0f)+translated),
            scaling*(glm::vec3(60.0f*1/6*1/2-15.0f,15.0f,-50.0f)+translated),
            scaling*(glm::vec3(60.0f*1/6*1/2+15.0f,15.0f,-50.0f)+translated)
    };

    std::vector<PointLight> pointLights(pointLightCount);


    for (int i = 0; i < pointLightCount; ++i) {
        PointLight pl;
        pl.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        pl.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        pl.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pl.constant = 1.0f;
        pl.linear = 0.006f;
        pl.quadratic = 0.0005f;
        pl.position = pointLightPositions[i];
        pointLights[i]=pl;
    }

    //init spotlight
    SpotLight spotLight;
    spotLight.position=scaling*(glm::vec3(60.0f*1/6*1/2,15.0f,-30.0f-(60.0f*1/6*1/2))+translated);
    spotLight.direction=glm::vec3(0.0f,-1.0f,0.0f);
    spotLight.ambient=glm::vec3( 0.05f, 0.05f, 0.05f);
    spotLight.diffuse=glm::vec3(1.0f, 1.0f, 1.0f);
    spotLight.specular=glm::vec3(1.0f, 1.0f, 1.0f);
    spotLight.constant=1.0f;
    spotLight.linear=0.002f;
    spotLight.quadratic=0.0008f;
    spotLight.cutOff=glm::cos(glm::radians(30.0f));
    spotLight.outerCutOff=glm::cos(glm::radians(45.0f));

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    //Shader ourShader("resources/shaders/2.model_lighting.vs", "resources/shaders/2.model_lighting.fs");
//    Shader wallShader("resources/shaders/rectangleObjectShader.vs","resources/shaders/rectangleObjectShader.fs");

//    RectangleObject rect("resources/textures/container.jpg");
    Shader generalShader("resources/shaders/rectangleObjectShader.vs","resources/shaders/rectangleObjectShader.fs");
    Room warehouse ("resources/textures/brickwall.jpg","resources/textures/brickwall.jpg","resources/textures/window.png","resources/textures/window.png");
    warehouse.buildHitboxes(&programState->game);

    LightCube light(glm::vec3(1.0f));
    Crosshair crosshair (glm::vec3(0.0f,1.0f,0.0f));
    Cube c1 ("resources/textures/container2.png","resources/textures/container2_specular.png");

    Shader rifleshader ("resources/shaders/rectangleObjectShader.vs","resources/shaders/rectangleObjectShader.fs");
    ModelObject rifle("resources/objects/Model_D0901C27/m4a1_s.obj");
    ModelObject animeGirl("resources/objects/Model_D0607085/D0607085.obj");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    programState->game.playerObj = new MoveableObject(glm::vec3(programState->camera.Position.x, programState->camera.Position.y - 5, programState->camera.Position.z), glm::vec3 (0.0f), 10.0f, 20.0f, 10.0f, 1, "red");
    programState->game.addMoveable(programState->game.playerObj);
    programState->game.playerObj->setShow(false);

    // render loop
    // -----------

    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);


        // render
        // ------
        glClearColor(programState->clearColor.r, programState->clearColor.g, programState->clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        crosshair.draw();

        // don't forget to enable shader before setting uniforms
//        ourShader.use();
//        pointLight.position = glm::vec3(4.0 * cos(currentFrame), 4.0f, 4.0 * sin(currentFrame));
//        ourShader.setVec3("pointLight.position", pointLight.position);
//        ourShader.setVec3("pointLight.ambient", pointLight.ambient);
//        ourShader.setVec3("pointLight.diffuse", pointLight.diffuse);
//        ourShader.setVec3("pointLight.specular", pointLight.specular);
//        ourShader.setFloat("pointLight.constant", pointLight.constant);
//        ourShader.setFloat("pointLight.linear", pointLight.linear);
//        ourShader.setFloat("pointLight.quadratic", pointLight.quadratic);
//        ourShader.setVec3("viewPosition", programState->camera.Position);
//        ourShader.setFloat("material.shininess", 32.0f);
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(programState->camera.Zoom),
                                                (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 600.0f);
        glm::mat4 view = programState->camera.GetViewMatrix();
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);

        // render the loaded model
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model,
//                               programState->backpackPosition); // translate it down so it's at the center of the scene
////        model = glm::rotate(model,(float)glfwGetTime()*10.0f,glm::vec3(0.0f,0.0f,1.0f));
//        model = glm::scale(model, glm::vec3(programState->backpackScale));    // it's a bit too big for our scene, so scale it down
//        ourShader.setMat4("model", model);
//        ourModel.Draw(ourShader);

        programState->game.gameTick(deltaTime, projection, view);

        light.setup(projection,view);

        warehouse.setup(projection,view,programState->camera.Position,dirLight,pointLights,spotLight);
        warehouse.draw();

        light.translate(scaling*(glm::vec3(30.0f,0.0f,-30.0f)+translated));
        light.scale(glm::vec3(5.0f,10.0f,1.0f));
        light.draw();

        light.translate(scaling*(glm::vec3(0.0f,15.0f,-30.0f+(60.0f*1/3))+translated));
        light.scale(glm::vec3(10.0f,5.0f,1.0f));
        light.draw();

        light.translate(scaling*(glm::vec3(-60.0f*1/3,15.0f,-30.0f)+translated));
        light.scale(glm::vec3(10.0f,5.0f,1.0f));
        light.draw();

        light.translate(scaling*(glm::vec3(60.0f*1/6*1/2+15.0f,15.0f,-50.0f)+translated));
        light.scale(glm::vec3(10.0f,5.0f,1.0f));
        light.draw();


        light.translate(scaling*(glm::vec3(60.0f*1/6*1/2-15.0f,15.0f,-50.0f)+translated));
        light.scale(glm::vec3(10.0f,5.0f,1.0f));
        light.draw();

        c1.setup(projection,view,programState->camera.Position,dirLight,pointLights,spotLight);

//        c1.translate(glm::vec3(0.0f,-10.0f,20.0f));
//        c1.scale(glm::vec3(10.0f,10.0f,10.0f));
//        c1.draw();
        c1.translate(glm::vec3(4.0f,2.0f,4.0f)*(glm::vec3(60.0f*1/6*1/2,-10.0f,-30.0f-(60.0f*1/6*1/2))+glm::vec3(0.0f,0.0f,20.0f)));
        c1.scale(glm::vec3(10.0f,10.0f,10.0f));
        c1.draw();

        rifle.setup(rifleshader,glm::mat4(1.0f),glm::mat4(1.0f),programState->camera.Position,dirLight,pointLights,spotLight);

        rifle.translate(glm::vec3(1.0f,-0.6f,0.5f));
        rifle.rotate(-40.0f,glm::vec3(0.0f,1.0f,0.0f));
        rifle.rotate(-20.0f,glm::vec3(1.0f,0.0f,0.0f));
        rifle.scale(glm::vec3(0.06f,0.05f,0.03f));
        rifle.draw(rifleshader);

        animeGirl.setup(generalShader,projection,view,programState->camera.Position,dirLight,pointLights,spotLight);
        animeGirl.translate(glm::vec3(0.0f,-27.0f,10.0f));
        animeGirl.scale(glm::vec3(2.5f,2.0f,2.5f));
        animeGirl.draw(generalShader);

        crosshair.draw();

        if (programState->ImGuiEnabled)
            DrawImGui(programState);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    programState->SaveToFile("resources/program_state.txt");
    delete programState;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(FORWARD, deltaTime, programState->game);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(BACKWARD, deltaTime, programState->game);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(LEFT, deltaTime, programState->game);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(RIGHT, deltaTime, programState->game);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        programState->game.shoot(programState->camera.Position, programState->camera.Front);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (programState->CameraMouseMovementUpdateEnabled)
        programState->camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    programState->camera.ProcessMouseScroll(yoffset);
}

void DrawImGui(ProgramState *programState) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    {
        static float f = 0.0f;
        ImGui::Begin("Hello window");
        ImGui::Text("Hello text");
        ImGui::SliderFloat("Float slider", &f, 0.0, 1.0);
        ImGui::ColorEdit3("Background color", (float *) &programState->clearColor);
        ImGui::DragFloat3("Backpack position", (float*)&programState->backpackPosition);
        ImGui::DragFloat("Backpack scale", &programState->backpackScale, 0.05, 0.1, 4.0);

        ImGui::DragFloat("pointLight.constant", &programState->pointLight.constant, 0.05, 0.0, 1.0);
        ImGui::DragFloat("pointLight.linear", &programState->pointLight.linear, 0.05, 0.0, 1.0);
        ImGui::DragFloat("pointLight.quadratic", &programState->pointLight.quadratic, 0.05, 0.0, 1.0);
        ImGui::End();
    }

    {
        ImGui::Begin("Camera info");
        const Camera& c = programState->camera;
        ImGui::Text("Camera position: (%f, %f, %f)", c.Position.x, c.Position.y, c.Position.z);
        ImGui::Text("(Yaw, Pitch): (%f, %f)", c.Yaw, c.Pitch);
        ImGui::Text("Camera front: (%f, %f, %f)", c.Front.x, c.Front.y, c.Front.z);
        ImGui::Checkbox("Camera mouse update", &programState->CameraMouseMovementUpdateEnabled);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        programState->ImGuiEnabled = !programState->ImGuiEnabled;
        if (programState->ImGuiEnabled) {
            programState->CameraMouseMovementUpdateEnabled = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}
