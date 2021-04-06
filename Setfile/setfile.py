# We need to simplify this with regular expressions.
from re import findall as regex


# Simple is-numeric function.
def is_numeric(str_input):
    
    # Check each character to figure out if we're dealing with a number.
    for char in str_input:
        if char not in ['0','1','2','3','4','5','6','7','8','9']:
            return False
        
    # If every character is a number, then treat this value as a number.
    return True


# Simple sanitization for arrays of inputs.
def check_array(array_input):
    
    # Create a temporary array to return.
    return_array = []
    
    # Check each character of each array value to figure out if we're dealing with a number or a boolean.
    for value in array_input:
        return_array.append(True) if value == 'TRUE' \
            else return_array.append(False) if value == 'FALSE' \
            else return_array.append(int(value)) if is_numeric(value) \
            else return_array.append(value)
                
    # Return our return array.
    return return_array


class Setfile(object):
    def __init__(self, filename):
        
        # Create a blank dictionary.
        self.items = {}
        
        try:
            
            # Open our settings file and gather all of the lines.
            with open(filename, 'r', encoding='utf8', errors='strict') as setfile:
                self.data = setfile.readlines()
            
        except Exception as e:
            
            # Set the settings file data if we fail to open the file.
            self.data = None
            
            # Then throw a generic exception.
            raise Exception(e)


    def parse(self):
        
        # Do not bother parsing the setting file data if there is no data to parse.
        if self.data is not None:
            
            # Sift through the setting file data line-by-line.
            for line in self.data:
                
                # Do not parse comments.
                if not line.startswith('//'):
                    
                    # We need to determine if we're declaring a variable.
                    tmp_decl = regex(r'(.*) \= (.*)\n', line)
                    for decl in tmp_decl:
                        
                        # Determine if our entry is a boolean or a number.
                        value = f'{decl[1]}'
                        
                        if decl[1] == 'TRUE':
                            value = True
                        elif decl[1] == 'FALSE':
                            value = False
                        elif is_numeric(decl[1]):
                            value = int(decl[1])
                        
                        # Update our dictionary with a new entry.
                        self.items.update({f'{decl[0]}': value})
                        
                    # We need to determine if we're declaring an array.
                    tmp_arr = regex(r'(.*) \=\> \[(.*)\]\n', line)
                    for arr in tmp_arr:
                        
                        # Update our dictionary with a new entry.
                        self.items.update({f'{arr[0]}': check_array(arr[1].split(', '))})
