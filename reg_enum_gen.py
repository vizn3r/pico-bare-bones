#!/usr/bin/env python3

import re
import sys

def parse_bit_range(bits_str):
    """Parse bit range like '31:21' or '20' and return (high, low, width)"""
    if ':' in bits_str:
        high, low = map(int, bits_str.split(':'))
        return high, low, high - low + 1
    else:
        bit = int(bits_str)
        return bit, bit, 1

def parse_register(text):
    """Parse register description and return list of fields"""
    fields = []
    lines = text.strip().split('\n')
    
    # Find where the bit descriptions start (after "Bits Description Type Reset")
    start_idx = 0
    for i, line in enumerate(lines):
        if 'Bits' in line and 'Description' in line and 'Type' in line:
            start_idx = i + 1
            break
    
    i = start_idx
    while i < len(lines):
        line = lines[i].strip()
        
        # Skip empty lines or enumerated values sections
        if not line or line.startswith('Enumerated') or line.startswith('0x'):
            i += 1
            continue
        
        # Match bit range at start of line
        match = re.match(r'^(\d+(?::\d+)?)\s+(.+)', line)
        if match:
            bits_str = match.group(1)
            rest = match.group(2)
            
            high, low, width = parse_bit_range(bits_str)
            
            # Check if reserved
            is_reserved = 'Reserved' in rest or rest.strip() == '-'
            
            if is_reserved:
                name = None
            else:
                # Try format: "FIELD_NAME: description"
                name_match = re.match(r'^([A-Z_0-9]+):', rest)
                if name_match:
                    name = name_match.group(1).lower()
                else:
                    # Try format: "FIELD_NAME RW|RO|... 0xvalue"
                    name_match = re.match(r'^([A-Z_0-9]+)\s+(RW|RO|WC|WO|SC|W1C|W1S)', rest)
                    if name_match:
                        name = name_match.group(1).lower()
                    else:
                        name = None
            
            fields.append({
                'high': high,
                'low': low,
                'width': width,
                'name': name
            })
        
        i += 1
    
    return fields

def generate_struct(fields, struct_name):
    """Generate C typedef union from fields"""
    # Sort fields by low bit (ascending)
    fields_sorted = sorted(fields, key=lambda f: f['low'])
    
    output = []
    output.append(f"typedef union {{")
    output.append(f"  struct {{")
    
    for field in fields_sorted:
        if field['name']:
            output.append(f"    uint32_t {field['name']} : {field['width']};")
        else:
            output.append(f"    uint32_t : {field['width']};")
    
    output.append(f"  }};")
    output.append(f"  uint32_t raw;")
    output.append(f"}} {struct_name};")
    
    return '\n'.join(output)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: ./parse_reg.py <struct_name>")
        print("Paste register description, then press Ctrl+D")
        sys.exit(1)
    
    struct_name = sys.argv[1]
    
    # Read from stdin
    text = sys.stdin.read()
    
    fields = parse_register(text)
    result = generate_struct(fields, struct_name)
    print(result)
