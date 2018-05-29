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

    it('should get value of shape from index', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        expect(blob).to.not.eql(undefined);
        expect(blob.shape()).to.not.eql(undefined);
        expect(blob.shape(0)).to.eql(num);
        expect(blob.shape(1)).to.eql(channels);
        expect(blob.shape(2)).to.eql(height);
        expect(blob.shape(3)).to.eql(width);
    })

    it('should get num axes of shape ', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        expect(blob).to.not.eql(undefined);
        expect(blob.num_axes()).to.not.eql(undefined);
        expect(blob.num_axes()).to.eql(4);
    })

    it('should get volume of slice by count', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        expect(blob).to.not.eql(undefined);

        expect(blob.count()).to.not.eql(undefined);
        expect(blob.count()).to.eql(num* channels* height * width);

        expect(blob.count(2)).to.not.eql(undefined);
        expect(blob.count(2)).to.eql(height * width);

        expect(blob.count(0,1)).to.not.eql(undefined);
        expect(blob.count(0,2)).to.eql(num* channels);
    })

    it('should calc CanonicalAxisIndex of blob', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        expect(blob).to.not.eql(undefined);
        expect(blob.CanonicalAxisIndex(-1)).to.not.eql(undefined);
        expect(blob.CanonicalAxisIndex(-1)).to.eql(3);
    })

    it('should get num,channels,height,width of blob', () => {
        const num = parseInt( Math.random() * 10);
        const channels = parseInt( Math.random() * 10);
        const height = parseInt( Math.random() * 10);
        const width = parseInt( Math.random() * 10);
        let blob = caffeNode.blob(num, channels, height, width);
        expect(blob).to.not.eql(undefined);

        expect(blob.num()).to.not.eql(undefined);
        expect(blob.num()).to.eql(num);
        
        expect(blob.channels()).to.not.eql(undefined);
        expect(blob.channels()).to.eql(channels);
        
        expect(blob.height()).to.not.eql(undefined);
        expect(blob.height()).to.eql(height);
        
        expect(blob.width()).to.not.eql(undefined);
        expect(blob.width()).to.eql(width);
    })


    
})