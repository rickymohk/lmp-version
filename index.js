const addon = require('./build/Release/lmpVersion');
module.exports = {
    getBluetoothLMPVersion: addon.getBluetoothLMPVersion
};