const { expect } = require('chai');
const caffeNode = require('../caffenode')
describe('Hello', () => {
    it('should call hello world', () => {
        expect(caffeNode.hello()).to.not.eql(undefined);
        expect(caffeNode.hello()).to.eql('world');
    })
})