

int main()
{
    auto root = mRenderer->getRootGroup();

    // ui
    auto ui = root->createGroup();
    auto uiCamera = ui->createCamera();
    uiCamera->setProjection(fr8::Renderer::Projection::Orthographic);

    // ui top bar
    auto topBar = ui->createGroup();
    topBar->setTransformPositionY(PixelToOrtho(window.height - topBarHeight));
    auto topBarBG = topBar->createModelPlane(Transform(Vec3(0.0f), Quat(Vec3(ToDeg(90.0f, 0.0f, 0.0f))), Vec3(1.0f)));
    topBarBG->setTexture(Material.grey);
    auto importButton = ui->createGr

    // ui import button

    // game world
    auto gameWorld = root->createGroup();
    auto player = gameWorld->createGroup();
    auto playerCamera = player->createCamera();
    auto playerCamera->setProjection(fr8::Renderer::Projection::Perspective);

    // render targets
    auto uiRenderTarget = renderer->createRenderTarget(window.width, window.height);
    auto gameWorldRenderTarget = renderer->createRenderTarget(window.width, window.height);

    uiCamera->drawTo(uiRenderTarget);
    playerCamera->drawTo(gameWorldRenderTarget);
    renderer->drawToWindow();
}



Node2D* CreateUIBackground(
    Node2D *parent, 
    std::wstring uiTileFile,
    uint32_t width,
    uint32_t height,
    )
{
    auto node = parent->createNode();

    auto topRight = node->createNode();
    auto topLeft = node->createNode();
    auto bottomRight = node->createNode();
    auto bottomLeft = node->createNode();
    auto top = node->createNode();
    auto bottom = node->createNode();
    auto right = node->createNode();
    auto left = node->createNode();
    auto middle = node->createNode();

    // load textures

    return node;
}


void ScaleUIBackground(Node2D *node, uint32_t width, uint32_t height)
{

}



void main()
{
    auto ui = renderer->createRenderGroup2D();

    auto background = CreateUIBackground(ui->getRoot(), "assets/textures/ui/bg.png");
    auto button = CreateUIBackground(background, "assets/textures/ui/button.png");
}
