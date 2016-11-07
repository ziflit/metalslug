/*
 * Configs.h
 *
 *  Created on: Oct 17, 2016
 *      Author: leandro
 */

#ifndef SRC_MODEL_CONFIGS_H_
#define SRC_MODEL_CONFIGS_H_

#include "../utils/Protocol.h"
#include <vector>

class ConfigsXML {
private:
    struct xmlConfig globalConf;
    vector<struct xmlBackground> backgroundsConfig;
    vector<struct xmlPlayer> playersConfig;
    vector<struct xmlEnemy> enemiesConfig;
    vector<struct xmlLvl> lvlsConfig;
    
public:

    ConfigsXML(){};
    virtual ~ConfigsXML(){};

    vector<struct xmlBackground> getBackgroundsConfig() {
        return backgroundsConfig;
    }

    void setBackgroundsConfig(vector<struct xmlBackground> backgroundsConfig) {
        this->backgroundsConfig = backgroundsConfig;
    }

    struct xmlConfig getGlobalConf() {
        return globalConf;
    }

    void setGlobalConf(struct xmlConfig globalConf) {
        this->globalConf = globalConf;
    }

    vector<struct xmlPlayer> getPlayersConfig() {
        return playersConfig;
    }

    void setPlayersConfig(vector<struct xmlPlayer> playersConfig) {
        this->playersConfig = playersConfig;
    }

    vector<struct xmlEnemy> getEnemiesConfig() {
        return enemiesConfig;
    }

    void setEnemiesConfig(vector<struct xmlEnemy> enemiesConfig) {
        this->enemiesConfig = enemiesConfig;
    }

    vector<struct xmlLvl> getLvlsConfig() {
        return lvlsConfig;
    }

    void setLvlsConfig(vector<struct xmlLvl> lvlsConfig) {
        this->lvlsConfig = lvlsConfig;
    }
};

#endif /* SRC_MODEL_CONFIGS_H_ */
