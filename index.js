const addon = require('./build/Release/lmpVersion');
module.exports = {
    getBluetoothLmpVersion: addon.getBluetoothLmpVersion
};