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

class Configs {
private:
    struct xmlConfig globalConf;
    vector<struct xmlBackground> backgroundsConfig;
    vector<struct xmlPlayer> spritesConfig;
public:

    Configs(){};
    virtual ~Configs(){};

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

    vector<struct xmlPlayer> getSpritesConfig() {
        return spritesConfig;
    }

    void setSpritesConfig(vector<struct xmlPlayer> spritesConfig) {
        this->spritesConfig = spritesConfig;
    }
};

#endif /* SRC_MODEL_CONFIGS_H_ */
