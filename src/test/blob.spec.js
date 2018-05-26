const { expect } = require('chai');
const caffeNode = require('../caffenode')
describe('Hello', () => {
    it('should create blob instance', () => {
        expect(caffeNode.blob()).to.not.eql(undefined);
    })
})