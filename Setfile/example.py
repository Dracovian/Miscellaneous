from setfile import Setfile

if __name__ == '__main__':
    try:
        sfile = Setfile('example.set')
        sfile.parse()
    
        print(sfile.items)
    except Exception as ex:
        print(ex)