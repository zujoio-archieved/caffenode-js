const { expect } = require('chai');
const caffeNode = require('../caffenode')
describe('Blob', () => {
    it('should create blob instance', () => {
        let blob = caffeNode.blob(1, 1, 1, 1);
        expect(blob).to.not.eql(undefined);
        console.log("blob.shape()", blob.shape())
        expect(blob.shape()).to.not.eql(undefined);
    })
})