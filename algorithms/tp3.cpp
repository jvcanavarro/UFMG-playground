
#include <bits/stdc++.h>

#define int long long

using namespace std;

template <typename T>
struct mcmf
{
    // https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/minCostMaxFlow.cpp

    struct edge
    {
        int to, rev, flow, cap; // para, id da reversa, fluxo, capacidade
        bool res;               // se eh reversa
        T cost;                 // custo da unidade de fluxo
        edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
        edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_)
            : to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
    };

    vector<vector<edge>> g;
    vector<int> par_idx, par;
    T inf;
    vector<T> dist;

    mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max() / 3) {}

    void add(int u, int v, int w, T cost)
    { // de u pra v com cap w e custo cost
        edge a = edge(v, g[v].size(), 0, w, cost, false);
        edge b = edge(u, g[u].size(), 0, 0, -cost, true);

        g[u].push_back(a);
        g[v].push_back(b);
    }

    vector<T> spfa(int s)
    { // nao precisa se nao tiver custo negativo
        deque<int> q;
        vector<bool> is_inside(g.size(), 0);
        dist = vector<T>(g.size(), inf);

        dist[s] = 0;
        q.push_back(s);
        is_inside[s] = true;

        while (!q.empty())
        {
            int v = q.front();
            q.pop_front();
            is_inside[v] = false;

            for (int i = 0; i < g[v].size(); i++)
            {
                auto [to, rev, flow, cap, res, cost] = g[v][i];
                if (flow < cap and dist[v] + cost < dist[to])
                {
                    dist[to] = dist[v] + cost;

                    if (is_inside[to])
                        continue;
                    if (!q.empty() and dist[to] > dist[q.front()])
                        q.push_back(to);
                    else
                        q.push_front(to);
                    is_inside[to] = true;
                }
            }
        }
        return dist;
    }
    bool dijkstra(int s, int t, vector<T> &pot)
    {
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        dist = vector<T>(g.size(), inf);
        dist[s] = 0;
        q.emplace(0, s);
        while (q.size())
        {
            auto [d, v] = q.top();
            q.pop();
            if (dist[v] < d)
                continue;
            for (int i = 0; i < g[v].size(); i++)
            {
                auto [to, rev, flow, cap, res, cost] = g[v][i];
                cost += pot[v] - pot[to];
                if (flow < cap and dist[v] + cost < dist[to])
                {
                    dist[to] = dist[v] + cost;
                    q.emplace(dist[to], to);
                    par_idx[to] = i, par[to] = v;
                }
            }
        }
        return dist[t] < inf;
    }

    pair<int, T> min_cost_flow(int s, int t, int flow)
    {
        vector<T> pot(g.size(), 0);
        pot = spfa(s); // mudar algoritmo de caminho minimo aqui

        int f = 0;
        T ret = 0;
        while (f < flow and dijkstra(s, t, pot))
        {
            for (int i = 0; i < g.size(); i++)
                if (dist[i] < inf)
                    pot[i] += dist[i];

            int mn_flow = flow - f, u = t;
            while (u != s)
            {
                mn_flow = min(mn_flow,
                              g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
                u = par[u];
            }

            ret += pot[t] * mn_flow;

            u = t;
            while (u != s)
            {
                g[par[u]][par_idx[u]].flow += mn_flow;
                g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
                u = par[u];
            }

            f += mn_flow;
        }

        return make_pair(f, ret);
    }
};

int32_t main()
{
    int n, m;
    int test_case = 1;
    while (cin >> n >> m)
    {
        mcmf<int> max_flow_min_cost(n);

        vector<vector<int>> edges(m, vector<int>(3));
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            edges[i] = {a - 1, b - 1, c};
        }

        int d, k;
        cin >> d >> k;

        for (int i = 0; i < m; ++i)
        {
            max_flow_min_cost.add(edges[i][0], edges[i][1], k, edges[i][2]);
            max_flow_min_cost.add(edges[i][1], edges[i][0], k, edges[i][2]);
        }

        // if (test_case > 1) {
        //     cout << '\n';
        // }
        cout << "Instancia " << test_case++ << endl;

        auto [flow, cost] = max_flow_min_cost.min_cost_flow(0, n - 1, d);
        if (flow < d)
        {
            cout << "impossivel\n";
        }
        else
        {
            cout << cost << endl;
        }
        cout << endl;
    }

    return 0;
}