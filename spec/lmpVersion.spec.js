const addon = require('../build/Release/lmpVersion');

describe("Bluetooth Addon", function() {
    it("should return a valid Bluetooth LMP version", function() {
        const lmpVersion = addon.getBluetoothLMPVersion();
        console.log({lmpVersion});
        expect(typeof lmpVersion).toBe("number");
    });
});