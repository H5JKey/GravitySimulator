#include "Simulation.h"

namespace ImGui {
    bool addObjMenu = false;
    bool editingMenu = false;
    bool otherSettingsMenu = false;
    bool objectsMenu = false;
    bool simulationSettingsMenu = false;
    struct ContextMenu {
        ContextMenu() {
            show = false;
            pos = { 0,0 };
        }
        bool show;
        ImVec2 pos;
        Object* selectedObject;
    };
    ContextMenu contextMenu;



    void setStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);

        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style.GrabRounding = style.FrameRounding = 2.3f;
    }
}

Simulation::Simulation():console(this) {

    selectedObj = nullptr;
    savedTimeSpeed = 0;
   

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    app.create(sf::VideoMode(), "Gravity Simulator", sf::Style::Fullscreen, settings);
    ImGui::SFML::Init(app);
    ImGui::setStyle();

    clock.restart();


    camera.reset(sf::FloatRect(0, 0, app.getSize().x, app.getSize().y));
    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    backGround = new BackGround("background.png", camera);

    loadSettings();

}

void Simulation::start() {
    objects.push_back(Object(2000000, 20, sf::Vector2f(960, 540), sf::Vector2f(0, 0), "Sun", sf::Color(255, 255, 255), true));
    objects.push_back(Object(300, 2, sf::Vector2f(960, 50), sf::Vector2f(500, 0), "Planet"));

    while (app.isOpen()) {
        update();
    }
}


void Simulation::update() {
    ellapsedTime = clock.restart();
    if (!physics.timeStop)
        timer += (sf::seconds(0.00007) * physics.timeSpeed);
    if (!physics.timeStop && physics.timeSpeed > 0)
        ParticlesSystem::update(ellapsedTime);
    updateEvents();
    updateGui();
    updateObjects();
    updateGraphics();

}

void Simulation::saveSettings() {
    std::ofstream ofs("settings.ini");
    ofs << "[Settings]\n";
    ofs << "DrawBackground=" + std::to_string(backGround->show) << '\n';
    ofs << "ShowFPS=" + std::to_string(fpsTracker.show) << '\n';
    ofs << "ShowOrbits=" + std::to_string(showOrbits) << '\n';
    ofs << "ShowTimer=" + std::to_string(timer.show) << '\n';
    ofs << "OrbitLifeTime=" + std::to_string(ParticlesSystem::getOrbitLifeTime().asMilliseconds()) << '\n';
}

void Simulation::loadSettings() {
    std::ifstream ifs("settings.ini");
    if (!ifs.bad()) {
        std::string s;
        ifs >> s;
        ifs >> s;
        backGround->show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        fpsTracker.show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        showOrbits = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        timer.show = bool(stoi(s.substr(s.find('=') + 1)));
        ifs >> s;
        ParticlesSystem::setOrbitLifeTime(sf::milliseconds(stoi(s.substr(s.find('=') + 1))));
    }
    else {
        fpsTracker.show = false;
        showOrbits = true;
        backGround->show = true;
        timer.show = false;
    }
}

void Simulation::updateObjects() {
   
    physics.update(objects, sf::seconds(0.00007));

    if (centerOfGravity.show)
        centerOfGravity = physics.calculateCenterOfGravity(forGravityCenter);


}


void Simulation::updateGraphics() {

    app.clear();
    if (backGround->show) {
        app.setView(app.getDefaultView());
        app.draw(*backGround);
    }

    app.setView(camera);
    for (auto& object : objects) {
        object.draw(app);
        if (!physics.timeStop && physics.timeSpeed != 0 && showOrbits)
            ParticlesSystem::add(new Pixel(object.properties.pos / powf(10, 3), object.properties.color, ParticlesSystem::getOrbitLifeTime()));
    }
    if (centerOfGravity.show)
        centerOfGravity.draw(app);

    ParticlesSystem::draw(app);


    if (fpsTracker.show) {
        app.setView(app.getDefaultView());
        fpsTracker.calculate(ellapsedTime);
        app.draw(fpsTracker);
        app.setView(camera);
    }
    if (timer.show) {
        app.setView(app.getDefaultView());
        timer.draw(app);
        app.setView(camera);
    }

    ImGui::SFML::Render(app);
    app.display();
}

void zoomViewAt(sf::Vector2i pixel, sf::View& view, sf::RenderWindow& window, float zoom)
{
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);
    window.setView(view);
}

void Simulation::updateEvents() {
    sf::Event event;
    while (app.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::MouseMoved)
            cursorPosition = app.mapPixelToCoords(sf::Mouse::getPosition());

        if (event.type == sf::Event::Closed)
            app.close();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space) && (!ImGui::GetIO().WantCaptureKeyboard))
            physics.timeStop = !physics.timeStop;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up) && (!ImGui::GetIO().WantCaptureKeyboard)) {
            physics.timeSpeed += 15;
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down) && (!ImGui::GetIO().WantCaptureKeyboard)) {
            physics.timeSpeed -= 15;
            physics.timeSpeed = std::max(physics.timeSpeed, 0.f);
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F1))
            console.show = !console.show;
       
        if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            for (auto& object : objects) {
                if (object.collide(cursorPosition)) {
                    copied = true;
                    copiedObject = object;
                    break;
                }
            }
        }

        if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            objects.push_back(copiedObject);
            
            for (auto& object : objects) {
                (objects.end() - 1)->properties.pos = cursorPosition * powf(10, 3);
            }
        }
        if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))) {
            sf::Vector2f mb = app.mapPixelToCoords(sf::Mouse::getPosition());
            objects.erase(std::remove_if(objects.begin(), objects.end(), [&](Object& object) {return object.collide(mb); }), objects.end());
            forGravityCenter.erase(std::remove_if(forGravityCenter.begin(), forGravityCenter.end(), [&](Object* object) {return object->collide(mb); }), forGravityCenter.end());
        }


        if (!ImGui::GetIO().WantCaptureMouse) {
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0) {
                    zoomViewAt(sf::Mouse::getPosition(), camera, app, 0.9);
                }
                else {
                    camera.zoom(1.1);
                }

            }
            static sf::Clock delta;//for double clicks
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                ImGui::contextMenu.show = false;
                sf::Vector2f mb = app.mapPixelToCoords(sf::Mouse::getPosition());
                if (!ImGui::addObjMenu) {
                    for (auto& object : objects) {
                        if (object.collide(mb)) {
                            if (delta.getElapsedTime().asMilliseconds() > 500) delta.restart();
                            else {
                                selectedObj = &object;
                                delta.restart();
                            }
                            break;
                        }
                    }
                }
                else {
                    newObj.properties.pos = mb * powf(10, 3);
                    objects.push_back(newObj);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                ImGui::contextMenu.show = true;
                ImGui::contextMenu.pos = sf::Mouse::getPosition();
                ImGui::contextMenu.selectedObject = nullptr;
                sf::Vector2f mb = app.mapPixelToCoords(sf::Mouse::getPosition());
                for (auto& object : objects) {
                    if (object.collide(mb)) {
                        ImGui::contextMenu.selectedObject = &object;
                        break;
                    }
                }
            }


        }
    }
    static sf::Vector2f previousMousePos;
    static sf::Vector2f cameraOffset;

    if (selectedObj == nullptr) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !ImGui::GetIO().WantCaptureMouse && !ImGui::addObjMenu) {
            sf::Vector2f currentmousePos = app.mapPixelToCoords(sf::Mouse::getPosition());
            cameraOffset = (currentmousePos - previousMousePos) * 0.7f;
        }
        else
            cameraOffset = { 0,0 };
        previousMousePos = app.mapPixelToCoords(sf::Mouse::getPosition());
    }

    sf::Time ellapsedTime = clock.restart();
    if (selectedObj != nullptr) {
        camera.setCenter(selectedObj->properties.pos / powf(10, 3));
        ImGui::editingMenu = true;
    }

    camera.move(-cameraOffset);
}

void Simulation::updateGui() {

    ImGui::SFML::Update(app, ellapsedTime);
    ImGui::Begin("Gravity simulation", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
    {

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..")) {
                    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileToLoad", "Choose file", ".sim", ".");
                }
                if (ImGui::MenuItem("Save")) {
                    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileToSave", "Choose file", ".sim", ".");
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Objects")) {
                if (ImGui::MenuItem("Add object")) {
                    ImGui::addObjMenu = true;
                    selectedObj = nullptr;
                }
                if (ImGui::MenuItem("View all objects"))
                    ImGui::objectsMenu = true;
                ImGui::otherSettingsMenu = false;
                ImGui::EndMenu();
            }


            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Simulation settings")) {
                    ImGui::simulationSettingsMenu = true;
                    ImGui::otherSettingsMenu = false;
                }
                if (ImGui::MenuItem("Other settings")) {
                    ImGui::simulationSettingsMenu = false;
                    ImGui::otherSettingsMenu = true;
                }
                ImGui::objectsMenu = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }


        if (ImGuiFileDialog::Instance()->Display("ChooseFileToSave"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::ofstream f(filePathName);
                f.close();
                Save newSaveFile(filePathName);
                newSaveFile.save(objects, camera.getCenter(), timer.get());
            }

            ImGuiFileDialog::Instance()->Close();
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileToLoad"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                Save saveFile(filePathName);
                sf::Vector2f center;
                sf::Time time;
                saveFile.load(objects, center, time);
                timer.set(time);
                camera.setCenter(center);
                ParticlesSystem::clear();
                centerOfGravity.show = false;
                selectedObj = nullptr;
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::Separator();
        if (ImGui::addObjMenu) {//Adding new object
            ImGui::Text("Name:");
            ImGui::InputText("##Name", &newObj.properties.name);
            ImGui::Separator();
            ImGui::Text("Mass:");
            ImGui::InputFloat("##Mass", &newObj.properties.mass, 50.f, 0);
            ImGui::Separator();
            ImGui::Text("Radius");
            ImGui::InputFloat("##Radius", &newObj.properties.radius,0.5,1);
            newObj.properties.radius = std::max(0.f, newObj.properties.radius);
            ImGui::Separator();
            ImGui::Text("Position:");
            float position[2] = {newObj.properties.pos.x/1000, newObj.properties.pos.y/1000 };
            ImGui::InputFloat2("##Position", position);
            newObj.properties.pos.x = position[0] * powf(10, 3);
            newObj.properties.pos.y = position[1] * powf(10, 3);

            ImGui::Text("Speed:");
            float* speed[2] = { &newObj.properties.speed.x, &newObj.properties.speed.y };
            ImGui::InputFloat2("##Speed", *speed);
            ImGui::Separator();
            ImGui::Text("Color:");
            float color[3] = { newObj.properties.color.r / 255.f,newObj.properties.color.g / 255.f ,newObj.properties.color.b / 255.f };
            ImGui::ColorEdit3("##SelectColor", color);
            newObj.properties.color = { static_cast<sf::Uint8>(color[0] * 255), static_cast<sf::Uint8>(color[1] * 255), static_cast<sf::Uint8>(color[2] * 255) };
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &newObj.properties.fixed);
            ImGui::Checkbox("Use in gravity center", &newObj.useForGravityCenter);
            ImGui::Checkbox("Affected by gravity", &newObj.properties.affectedByGravity);
            ImGui::Checkbox("Affectes others", &newObj.properties.affectsOthers);
            ImGui::Separator();
            if (ImGui::Button("Create"))
                objects.push_back(newObj);
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::addObjMenu = false;
        }
        else if (ImGui::otherSettingsMenu) {//Other settings menu
            ImGui::Checkbox("Draw background", &backGround->show);
            ImGui::Separator();
            ImGui::Checkbox("Show FPS", &fpsTracker.show);
            ImGui::Separator();
            ImGui::Checkbox("Show orbits", &showOrbits);
            if (showOrbits) {
                int t = ParticlesSystem::getOrbitLifeTime().asMilliseconds();
                ImGui::SliderInt("Orbit life time", &t, 0, 50000);
                ParticlesSystem::setOrbitLifeTime(sf::milliseconds(t));
            }
            ImGui::Separator();
            ImGui::Checkbox("Show timer", &timer.show);

            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::otherSettingsMenu = false;

        }
        else if (ImGui::simulationSettingsMenu) {//Simulation settings menu
            ImGui::Checkbox("Gravity on", &physics.gravityOn);
            if (physics.gravityOn) {
                ImGui::Text("Gravity range");
                ImGui::SliderFloat("##Gravity range", &physics.gravityRange, 0, 500);
            }
            ImGui::Separator();
            ImGui::RadioButton("Destroy on collision", &physics.selectedCollisionOption, 0);

            ImGui::RadioButton("Solve collision", &physics.selectedCollisionOption, 1);
            if (physics.selectedCollisionOption == 1) {
                ImGui::Text("Restitution coefficient");
                ImGui::SliderFloat("##restitution coefficientSlider", &physics.restitutionCoefficient, 0, 1);
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                ImGui::simulationSettingsMenu = false;

        }
        else if (ImGui::objectsMenu) {//Objects Menu
            ImGui::Checkbox("Show center of gravity", &centerOfGravity.show);
            ImGui::ListBoxHeader("##ObjectsList"); {
                forGravityCenter.clear();
                for (int i = 0; i < objects.size(); i++) {
                    if (objects[i].properties.name == "") continue;
                    if (ImGui::Selectable((objects[i].properties.name + "##" + std::to_string(i)).c_str(), false, 0, ImVec2(ImGui::GetWindowContentRegionWidth() - 25, 15))) {
                        selectedObj = &objects[i];
                    }
                    ImGui::SameLine();
                    if (centerOfGravity.show) {
                        ImGui::Checkbox(std::to_string(i).c_str(), &objects[i].useForGravityCenter);

                        if (objects[i].useForGravityCenter)
                            forGravityCenter.push_back(&objects[i]);
                    }
                    else {
                        if (ImGui::Button(("-##" + std::to_string(i)).c_str()))
                            objects.erase(objects.begin() + i);
                    }
                }
            }
            ImGui::ListBoxFooter();
            if (ImGui::Button("Clear"))
                objects.clear();
            if (ImGui::Button("Exit"))
                ImGui::objectsMenu = false;
        }
        else {//Main menu
            ImGui::Text("Time Speed");
            ImGui::SliderFloat("##TimeSpeed", &physics.timeSpeed, 0, 1500);
            ImGui::Checkbox("Stop time\t Press Space", &physics.timeStop);
            if (ImGui::Button("Reset timer"))
                timer.reset();

            ImGui::Separator();
            if (ImGui::Button("Exit"))
                app.close();
        }
    }
    ImGui::End();
    if (ImGui::editingMenu) {//Editing selected object
        ImGui::Begin("##ObjectMenu", nullptr, ImGuiWindowFlags_NoResize); {
            ImGui::Text("Name:");
            ImGui::InputText("##Name", &selectedObj->properties.name);
            ImGui::Separator();
            ImGui::Text("Mass:");
            ImGui::InputFloat("##Mass", &selectedObj->properties.mass, 50.f);
            ImGui::Separator();
            ImGui::Text("Radius");
            ImGui::InputFloat("##Radius", &selectedObj->properties.radius,0.5,1);
            selectedObj->properties.radius = std::max(0.f, selectedObj->properties.radius);
            ImGui::Separator();
            ImGui::Text("Speed:");
            float* speed[2] = { &selectedObj->properties.speed.x, &selectedObj->properties.speed.y };
            ImGui::InputFloat2("##Speed", *speed);
            ImGui::Separator();
            ImGui::Text("Color:");
            float color[3] = { static_cast<float>(selectedObj->properties.color.r / 255.f), static_cast<float>(selectedObj->properties.color.g / 255.f) ,static_cast<float>(selectedObj->properties.color.b / 255.f) };
            ImGui::ColorEdit3("##Color", color);
            selectedObj->properties.color = { static_cast<sf::Uint8>(color[0] * 255), static_cast<sf::Uint8>(color[1] * 255), static_cast<sf::Uint8>(color[2] * 255) };
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Checkbox("Fixed", &selectedObj->properties.fixed);
            ImGui::Checkbox("Use in gravity center",&selectedObj->useForGravityCenter);
            ImGui::Checkbox("Affected by gravity", &selectedObj->properties.affectedByGravity);
            ImGui::Checkbox("Affectes others", &selectedObj->properties.affectsOthers);
            if (ImGui::Button("Copy")) {
                copiedObject = *selectedObj;
                copiedObject.useForGravityCenter = false;
                copied = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Delete")) {
                objects.erase(std::remove_if(objects.begin(), objects.end(), [&](const auto& object) {return &object == selectedObj; }), objects.end());
                forGravityCenter.erase(std::remove_if(forGravityCenter.begin(), forGravityCenter.end(), [&](const auto& object) {return object == selectedObj; }), forGravityCenter.end());
                selectedObj = nullptr;
                ImGui::editingMenu = false;
            }
            ImGui::Separator();
            if (ImGui::Button("Exit"))
                selectedObj = nullptr;
            ImGui::editingMenu = false;
        }
        ImGui::End();
    }



    //Context menu

    if (ImGui::contextMenu.show) {
        ImGui::SetNextWindowPos(ImGui::contextMenu.pos);
        ImGui::Begin("Context menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        if (ImGui::Button("Paste    Ctrl+V", { 150,20 })) {
            if (copied) {
                objects.push_back(copiedObject);
                sf::Vector2f pos = app.mapPixelToCoords(ImGui::contextMenu.pos);

                (objects.end() - 1)->properties.pos = pos * powf(10, 3);;
                ImGui::contextMenu.show = false;
            }
        }

        if (ImGui::contextMenu.selectedObject) {
            if (ImGui::Button("Copy     Ctrl+C", { 150,20 })) {
                copied = true;
                copiedObject = *ImGui::contextMenu.selectedObject;
                copiedObject.useForGravityCenter = false;
                ImGui::contextMenu.show = false;
            }
            if (!ImGui::contextMenu.selectedObject->useForGravityCenter) {
                if (ImGui::Button("Use            ", { 150,20 })) {
                    ImGui::contextMenu.selectedObject->useForGravityCenter = true;
                }
            }
            if (ImGui::contextMenu.selectedObject->useForGravityCenter) {
                if (ImGui::Button("Not consider  ", { 150,20 })) {
                    ImGui::contextMenu.selectedObject->useForGravityCenter = false;
                }
            }
            if (ImGui::Button("Delete         ", { 150,20 })) {
                objects.erase(std::remove_if(objects.begin(), objects.end(), [&](const auto& object) {return &object == ImGui::contextMenu.selectedObject; }), objects.end());
                selectedObj = nullptr;
                ImGui::contextMenu.show = false;
            }
        }
        else {
            auto color = ImGui::GetStyle().Colors[ImGuiCol_Button];
            ImGui::PushStyleColor(ImGuiCol_Button, { color.x,color.y,color.z,color.w / 2 });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { color.x,color.y,color.z,color.w / 2 });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, { color.x,color.y,color.z,color.w / 2 });
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);

            ImGui::Button("Copy     Ctrl+C", { 150,20 });
            ImGui::Button("Use            ", { 150,20 });
            ImGui::Button("Delete         ", { 150,20 });

            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }


        ImGui::End();
    }


    //Console
    if (console.show) {     
        ImGui::SetNextWindowSize(ImVec2(app.getSize().x, 40));
        ImGui::SetNextWindowPos(ImVec2(0, app.getSize().y - 40));
        ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        {
            std::string consoleCommand;
            ImGui::SetNextItemWidth(app.getSize().x - 15);
            if (ImGui::InputText("##Console", &consoleCommand, ImGuiInputTextFlags_EnterReturnsTrue)) {
                console.handleCommand(consoleCommand);
            }
        }
        ImGui::End();
    }
}

Simulation::~Simulation() {
    ImGui::SFML::Shutdown();
    delete(backGround);
    saveSettings();
}
