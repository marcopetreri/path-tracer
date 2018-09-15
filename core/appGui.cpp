#include "appGui.hpp"
#include "geometry/ray.hpp"

AppGUI::AppGUI(int width, int heigth, const std::string & name, bool fs): nanogui::Screen(Eigen::Vector2i(width, heigth), name, true, fs){
  using namespace nanogui;

  w = new World();

  auto buttons = new Window(this, "Controls");
  buttons->setPosition(Vector2i(0, 0));
  buttons->setLayout(new BoxLayout(Orientation::Vertical, Alignment::Middle, 10, 5));

  Button * b = new Button(buttons, "Build", ENTYPO_ICON_TOOLS);
  b->setBackgroundColor(Color(0, 0, 255, 25));
  b->setCallback([&] {
    w->buildScene(&scenaBaz2);
  });

  b = new Button(buttons, "Render", ENTYPO_ICON_CAMERA);
  b->setBackgroundColor(Color(0, 255, 0, 25));
  b->setCallback([&] {
    w->renderScene();
    int e = nvgCreateImage(this->nvgContext(), "rendering.bmp", 0);
    viewer->setImage(e);
  });

  b = new Button(buttons, "Save", ENTYPO_ICON_SAVE);
  b->setCallback([&] {  });

  auto img_window = new Window(this, "Rendering");
  img_window->setPosition(Vector2i(100, 0));
  img_window->setLayout(new GroupLayout());

  viewer = new ImageView(img_window);
  viewer->setFixedSize(Vector2i(800, 600));

  performLayout(mNVGContext);

  mShader.init(
    /* An identifying name */
    "a_simple_shader",

    /* Vertex shader */
    "#version 330\n"
    "uniform mat4 modelViewProj;\n"
    "in vec3 position;\n"
    "void main() {\n"
    "    gl_Position = modelViewProj * vec4(position, 1.0);\n"
    "}",

    /* Fragment shader */
    "#version 330\n"
    "out vec4 color;\n"
    "uniform float intensity;\n"
    "void main() {\n"
    "    color = vec4(vec3(intensity), 1.0);\n"
    "}"
  );

  MatrixXu indices(3, 2); /* Draw 2 triangles */
        indices.col(0) << 0, 1, 2;
        indices.col(1) << 2, 3, 0;

        MatrixXf positions(3, 4);
        positions.col(0) << -1, -1, 0;
        positions.col(1) <<  1, -1, 0;
        positions.col(2) <<  1,  1, 0;
        positions.col(3) << -1,  1, 0;

        mShader.bind();
        mShader.uploadIndices(indices);
        mShader.uploadAttrib("position", positions);
        mShader.setUniform("intensity", 0.5f);

}

AppGUI::~AppGUI(){
  mShader.free();
}

bool AppGUI::keyboardEvent(int key, int scancode, int action, int modifiers){
    if (Screen::keyboardEvent(key, scancode, action, modifiers))
        return true;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        setVisible(false);
        return true;
    }
    return false;
}

void AppGUI::draw(NVGcontext *ctx){
    /* Draw the user interface */
    Screen::draw(ctx);
}

void AppGUI::drawContents(){
    using namespace nanogui;

    mShader.bind();

    Matrix4f mvp;
    mvp.setIdentity();
    mvp.topLeftCorner<3,3>() = Matrix3f(Eigen::AngleAxisf((float) glfwGetTime()*2,  Vector3f::UnitZ()))*.5;

    mvp.row(0) *= (float) mSize.y() / (float) mSize.x();

    mShader.setUniform("modelViewProj", mvp);
    mShader.setUniform("intensity", (float)sin(glfwGetTime()));

    /* Draw 2 triangles starting at index 0 */
    mShader.drawIndexed(GL_TRIANGLES, 0, 2);


}
