#pragma once

#include <functional>
#include <tinyxml2/tinyxml2.h>

#include <filesystem>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace anm2
{
  enum Type
  {
    NONE,
    ROOT,
    LAYER,
    NULL_,
    TRIGGER
  };

  using TextureCallback = std::function<std::shared_ptr<void>(const std::filesystem::path&)>;
  using SoundCallback = std::function<std::shared_ptr<void>(const std::filesystem::path&)>;

  class Vec2
  {
  public:
    float x{};
    float y{};
  };

  class Vec3
  {
  public:
    float r{};
    float g{};
    float b{};
  };

  class Vec4
  {
  public:
    float r{};
    float g{};
    float b{};
    float a{};
  };

  class Info
  {
  public:
    std::string createdBy{"robot"};
    std::string createdOn{};
    int fps = 30;
    int version{};

    Info() = default;
    Info(tinyxml2::XMLElement*);
  };

  class Spritesheet
  {
  public:
    std::filesystem::path path{};
    std::shared_ptr<void> userData{};

    Spritesheet(tinyxml2::XMLElement*, int&, TextureCallback = nullptr);
  };

  class Layer
  {
  public:
    std::string name{"New Layer"};
    int spritesheetID{-1};
    Layer(tinyxml2::XMLElement*, int&);
  };

  class Null
  {
  public:
    std::string name{"New Null"};
    bool isShowRect{};
    Null(tinyxml2::XMLElement*, int&);
  };

  class Event
  {
  public:
    std::string name{"New Event"};
    Event(tinyxml2::XMLElement*, int&);
  };

  class Sound
  {
  public:
    std::filesystem::path path{};
    std::shared_ptr<void> userData{};

    Sound(tinyxml2::XMLElement*, int&, SoundCallback = nullptr);
  };

  class Content
  {
  public:
    std::map<int, Spritesheet> spritesheets{};
    std::map<int, Layer> layers{};
    std::map<int, Null> nulls{};
    std::map<int, Event> events{};
    std::map<int, Sound> sounds{};

    Content() = default;
    Content(tinyxml2::XMLElement*, TextureCallback = nullptr, SoundCallback = nullptr);
  };

  struct Frame
  {
    Vec2 crop{};
    Vec2 position{};
    Vec2 pivot{};
    Vec2 size{};
    Vec2 scale{};
    float rotation{};
    int duration{};
    Vec4 tint{1.0f, 1.0f, 1.0f, 1.0f};
    Vec3 colorOffset{};
    bool isInterpolated{};
    int eventID{-1};
    int soundID{-1};
    int atFrame{-1};

    bool isVisible{true};

    Frame() = default;
    Frame(tinyxml2::XMLElement*, Type);
  };

  class Item
  {
  public:
    std::vector<Frame> frames{};
    bool isVisible{};

    Item() = default;
    Item(tinyxml2::XMLElement*, Type, int&);
  };

  class Animation
  {
  public:
    std::string name{"New Animation"};
    int frameNum{};
    bool isLoop{};

    Item rootAnimation{};
    std::unordered_map<int, Item> layerAnimations{};
    std::vector<int> layerOrder{};
    std::map<int, Item> nullAnimations{};
    Item triggers{};

    Animation() = default;
    Animation(tinyxml2::XMLElement*);
  };

  class Animations
  {
  public:
    std::string defaultAnimation{};
    std::vector<Animation> items{};

    Animations() = default;
    Animations(tinyxml2::XMLElement*);
  };

  class Anm2
  {
  public:
    Info info;
    Content content{};
    Animations animations{};

    Anm2() = default;
    Anm2(const std::filesystem::path&, TextureCallback = nullptr, SoundCallback = nullptr);
  };
}
