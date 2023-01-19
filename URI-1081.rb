# 1081 - DFSr - Depth Hierarchy
# Challenge Link: https://www.beecrowd.com.br/judge/en/problems/view/1081
# Score: Wrong answer (5%)
# Alfredo Diani

class Vertice
    attr_accessor :cor

    def initialize
        @cor = 'b'
    end
end

class Grafo
    attr_accessor :num_v, :num_e, :matAdj, :listaVertices

    def initialize(v, e)
        @num_v = v
        @num_e = e
        @matAdj = Array.new(v) {Array.new(v, false)}
        @listaVertices = []
        aloca_vertices
    end

    def add_aresta(x, y)
        @matAdj[x][y] = true
    end

    def aloca_vertices
        @listaVertices = []
        (0...@num_v).each do |i|
            @listaVertices << Vertice.new
        end
    end
    
    def reset_vertices
        @listaVertices.each {|vert| vert.cor = 'b'}
    end
end

def DFS_visit(graf, vert, nivel, path_count, starting_vert)
    ret = false
    nivel += 1
    graf.listaVertices[vert].cor = 'c'
    (0...graf.num_v).each do |i|
        if graf.matAdj[vert][i]
            ret = true
            path_count += 1
            nivel.times {print "  "}
            if graf.listaVertices[i].cor != 'b'
                print "#{vert}-#{i}"
            else
                print "#{vert}-#{i} pathR(G,#{i})"
            end
            puts
            if graf.listaVertices[i].cor == 'b'
                DFS_visit(graf, i, nivel, path_count, starting_vert)
            end
        end
    end
    if path_count == graf.num_e
        graf.listaVertices[vert].cor = 'b' if vert != starting_vert
        path_count = 0
        return
    end
    ret
end

# Example usage
num_tests = gets.to_i
num_tests.times do |i|
    puts "Caso #{i+1}:"
    v, e = gets.split.map(&:to_i)
    graf = Grafo.new(v, e)
    e.times do
        x, y = gets.split.map(&:to_i)
        graf.add_aresta(x, y)
    end
    nivel = 0
    path_count = 0
    (0...graf.num_v).each do |j|
        if graf.listaVertices[j].cor == 'b'
            path_count = 0
            if DFS_visit(graf, j, nivel, path_count, j)
                puts
            end
        end
    end
    graf.reset_vertices
    puts if i != num_tests - 1
end

