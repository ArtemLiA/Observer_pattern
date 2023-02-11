#include <iostream>
#include <list>

class WeatherData;

class Observers{
protected:
    WeatherData* wd1 = nullptr;
    WeatherData* wd2 = nullptr;
public:
    virtual void update(WeatherData* data) = 0;
    virtual ~Observers(){
        delete wd1;
        delete wd2;
    };
};

class WeatherData{
protected:
    float humidity;
    float temperature;
    float pressure;
    std::string type;
    std::list<Observers*> obs;
    virtual void Update(float h, float t, float p) = 0;
    WeatherData(float h, float t, float p): humidity(h), temperature(t), pressure(p) {};
};

class SeaWeather: WeatherData{
    bool is_storm;
    float wind_direction, wave_high, rainfall;
public:
    SeaWeather(float h, float t, float p, bool is_s,
               float w_d, float w_h, float r): WeatherData(h, t, p) {
        type = "SeaWeather";
        is_storm = is_s;
        wind_direction = w_d;
        wave_high = w_h;
        rainfall = r;
    };

    void Notify(){
        for (auto it = obs.begin(); it != obs.end(); it++){
            (*it)->update(this);
        }
        std::cout << "Air weather data successfully recorded!" << std::endl;
    };

};

class AirWeather: WeatherData{
    bool is_wind_share;
    float wind_direction, wind_speed, airport_pressure, visibility;
public:
    AirWeather(float h, float t, float p, bool is_w_s,
               float w_d, float w_s,float a_p, float v): WeatherData(h, t, p){
        is_wind_share = is_w_s;
        wind_direction = w_d;
        wind_speed = w_s;
        airport_pressure = a_p;
        visibility = is_w_s;
        type = "AirWeather";
    };
    
    void Notify(){
        for (auto it = obs.begin(); it != obs.end(); it++){
            (*it)->update(this);
        }
        std::cout << "Air weather data successfully recorded!" << std::endl;
    };
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
