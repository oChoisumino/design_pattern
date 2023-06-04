#include <iostream>

using namespace std;

#define MAX_OBSERVER_NUM (100U)
class Observer {
    public:
        virtual ~Observer() = default;
        int idx;
        virtual void update(float temperature, float humidity, float pressure) {}
};

class DisplayElement {
    public:
        virtual ~DisplayElement() = default;
        virtual void display() {}
};

class Subject {
    public:
        virtual ~Subject() = default;
        virtual void registerObserver(Observer *o) {}
        virtual void removeObserver(Observer *o) {}
        virtual void notifyObservers() {}
};

class WeatherData : public Subject {
    private:
        Observer *observers[MAX_OBSERVER_NUM];
        float temperature;
        float humidity;
        float pressure;
        int cnt;
    public:
        WeatherData() {
            cnt = 0;
            for (int i = 0; i < MAX_OBSERVER_NUM; i++) {
                observers[i] = NULL;
            }
        }
    
        void registerObserver(Observer *observer) {
            observers[cnt] = observer;
            observer->idx = cnt;
            cnt++;
        }

        void removeObserver(Observer *observer) {
            for (int i = observer->idx; i < cnt; i++) {
                observers[i] = observers[i+1];
            }
            cnt--;
        }

        void notifyObservers() {
            for (int i = 0; i < cnt; i++) {
                observers[i]->update(temperature, humidity, pressure);
            }
        }

        void measurementsChanged() {
            notifyObservers();
        }

        void setMeasurements(float temperature, float humidity, float pressure) {
            this->temperature = temperature;
            this->humidity = humidity;
            this->pressure = pressure;
            measurementsChanged();
        }
};
class CurrentConditionsDisplay : public Observer, DisplayElement {
    private:
        float temperature;
        float humidity;
        WeatherData *weatherData;
    public:
        CurrentConditionsDisplay(WeatherData *weatherData) {
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
        }
        void display() {
            cout << "현재 상태 : 온도 " << temperature << "도, 습도 " << humidity << endl;
        }
        void update(float temperature, float humidity, float pressure) {
            this->temperature = temperature;
            this->humidity = humidity;
            display();
        }
};

class StatisticsDisplay : public Observer, DisplayElement {
    private:
        float tempSum;
        float maxTemp;
        float minTemp;
        int numReadings;
        WeatherData *weatherData;
    public:
        StatisticsDisplay(WeatherData *weatherData) {
            this->weatherData = weatherData;
            this->tempSum = 0.0f;
            this->maxTemp = 0.0f;
            this->minTemp = 1000.0f;
            weatherData->registerObserver(this);
        }
        void display() {
            cout << "Avg/Max/Min temperature = "  << (tempSum / numReadings) << "/" << maxTemp << "/" << minTemp << endl;
        }
        void update(float temperature, float humidity, float pressure) {
            tempSum = tempSum + temperature;
            numReadings++;
            if (temperature > maxTemp) {
                maxTemp = temperature;
            }
            if (temperature < minTemp) {
                minTemp = temperature;
            }
            display();
        }
};

class ForecastDisplay : public Observer, DisplayElement {
    private:
        float currentPressure;
        float lastPressure;
        WeatherData *weatherData;
    public:
        ForecastDisplay(WeatherData *weatherData) {
            this->weatherData = weatherData;
            this->lastPressure = 0.0f;
            this->currentPressure = 29.2f;
            weatherData->registerObserver(this);
        }
        void display() {
            cout << "Forecast: " << endl ;
            if (currentPressure > lastPressure) {
                cout << "Improving weather on the way!" << endl;
            } else if (currentPressure == lastPressure) {
                cout << "More of the same" << endl;
            } else { // currentPressure < lastPressure
                cout << "Watch out for cooler, rainy weather" << endl;
            }
        }
        void update(float temperature, float humidity, float pressure) {
            lastPressure = currentPressure;
            currentPressure = pressure;
            display();
        }
};

int main(void) 
{
    WeatherData weatherData;

    CurrentConditionsDisplay ccDisplay = CurrentConditionsDisplay(&weatherData);
    StatisticsDisplay stDisplay = StatisticsDisplay(&weatherData);
    ForecastDisplay fcDisplay = ForecastDisplay(&weatherData);

    weatherData.setMeasurements(80, 65, 30.4f);
    weatherData.setMeasurements(82, 70, 29.2f);
    weatherData.setMeasurements(78, 90, 29.4f);

    return 0;
}