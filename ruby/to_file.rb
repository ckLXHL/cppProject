module ToFile
	def filename
		"object_#{self.object_id}.txt"
	end
	def to_f
		File.open(filename,'w') {|f| f.write(to_s)}
	end
	def f_to_str 
		File.open(filename,'r') {|f| puts f.read}
	end
end
class Person
	include ToFile
	attr_accessor :name
	def initialize(name)
		@name = name
	end
	def to_s
		name
	end
end
a = Person.new('matz')
a.to_f
a.f_to_str
