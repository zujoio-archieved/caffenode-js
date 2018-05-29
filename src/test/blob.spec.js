const { expect } = require('chai');
const caffeNode = require('../caffenode')
describe('Blob', () => {
    it('should create blob instance (num, channels, height, width)', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        expect(blob).to.not.eql(undefined);
        expect(blob.shape()).to.not.eql(undefined);

        expect(blob.shape()[0]).to.not.eql(undefined);
        expect(blob.shape()[0]).to.eql(num);

        expect(blob.shape()[1]).to.not.eql(undefined);
        expect(blob.shape()[1]).to.eql(channels);

        expect(blob.shape()[2]).to.not.eql(undefined);
        expect(blob.shape()[2]).to.eql(height);

        expect(blob.shape()[3]).to.not.eql(undefined);
        expect(blob.shape()[3]).to.eql(width);
    })

    it('should create blob instance [num, channels, height, width]', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob([num, channels, height, width]);
        expect(blob).to.not.eql(undefined);
        expect(blob.shape()).to.not.eql(undefined);

        expect(blob.shape()[0]).to.not.eql(undefined);
        expect(blob.shape()[0]).to.eql(num);

        expect(blob.shape()[1]).to.not.eql(undefined);
        expect(blob.shape()[1]).to.eql(channels);

        expect(blob.shape()[2]).to.not.eql(undefined);
        expect(blob.shape()[2]).to.eql(height);

        expect(blob.shape()[3]).to.not.eql(undefined);
        expect(blob.shape()[3]).to.eql(width);
    })

    it('should reshape blob with (num, channels, height, width)', () => {
        let blob = caffeNode.blob(1, 1, 1, 1);

        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        blob.Reshape(num, channels, height, width);

        expect(blob).to.not.eql(undefined);
        expect(blob.shape()).to.not.eql(undefined);

        expect(blob.shape()[0]).to.not.eql(undefined);
        expect(blob.shape()[0]).to.eql(num);

        expect(blob.shape()[1]).to.not.eql(undefined);
        expect(blob.shape()[1]).to.eql(channels);

        expect(blob.shape()[2]).to.not.eql(undefined);
        expect(blob.shape()[2]).to.eql(height);

        expect(blob.shape()[3]).to.not.eql(undefined);
        expect(blob.shape()[3]).to.eql(width);
    })

    it('should reshape blob with [num, channels, height, width]', () => {
        let blob = caffeNode.blob([1, 1, 1, 1]);

        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        blob.Reshape([num, channels, height, width]);

        expect(blob).to.not.eql(undefined);
        expect(blob.shape()).to.not.eql(undefined);

        expect(blob.shape()[0]).to.not.eql(undefined);
        expect(blob.shape()[0]).to.eql(num);

        expect(blob.shape()[1]).to.not.eql(undefined);
        expect(blob.shape()[1]).to.eql(channels);

        expect(blob.shape()[2]).to.not.eql(undefined);
        expect(blob.shape()[2]).to.eql(height);

        expect(blob.shape()[3]).to.not.eql(undefined);
        expect(blob.shape()[3]).to.eql(width);
    })

    it('should reshape blob like other blob', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let other = caffeNode.blob(num, channels, height, width);
        let blob = caffeNode.blob(num, channels, height, width);
        blob.ReshapeLike(other);

        expect(blob).to.not.eql(undefined);
        expect(blob.shape()).to.not.eql(undefined);
        expect(blob.shape()).to.eql([num, channels, height, width]);
    })

    it('should convert blob shape into string', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        const shapeStr = blob.shape_string();
        expect(shapeStr).to.not.eql(undefined);
        expect(shapeStr).to.eql(`${num} ${channels} ${height} ${width} (${num * channels * height * width})`);
    });

    
    
})