const { expect } = require('chai');
const caffeNode = require('../caffenode')
describe('Blob', () => {
    it('should create blob instance', () => {
        let blob = caffeNode.blob();
        expect(blob).to.not.eql(undefined);
         blob = caffeNode.blob(1,1,1,1)
    })
})