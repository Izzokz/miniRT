# miniRT

## 🦄️ Explications du Ray Tracing

Le ray tracing (lancer de rayons) est une technique de rendu graphique qui simule le parcours de la lumière. Pour chaque pixel de l'image, on lance un rayon depuis la caméra à travers ce pixel dans la scène 3D. On calcule ensuite l'intersection de ce rayon avec les objets de la scène pour déterminer la couleur du pixel.

### Vecteurs et Rayons
-   **Vecteurs**: La base du ray tracing. Ils représentent des positions, des directions ou des normales de surface sous la forme de coordonnées (x, y, z).
-   **Rayons**: Un rayon est défini par une origine (un point) et un vecteur direction normalisé. Il modélise le trajet d'un photon. La fonction `ft_new_ray` initialise un rayon à partir d'un point d'origine et d'un point cible.

### Intersections avec les Objets
Le cœur du ray tracing consiste à trouver le point d'intersection le plus proche entre un rayon et un objet. Cela se fait en résolvant un système d'équations : l'équation paramétrique du rayon et l'équation de la surface de l'objet.

-   **Sphère**: L'intersection est trouvée en résolvant une équation du second degré. Il peut y avoir zéro, une ou deux intersections.
-   **Plan**: L'intersection est trouvée en résolvant une équation du premier degré, beaucoup plus simple. Il n'y a qu'une seule intersection possible.
-   **Cylindre**: Le calcul est plus complexe. Il faut tester l'intersection avec la surface latérale (le "corps") et avec les deux disques qui ferment le cylindre (les "caps").
-   **Cône**: Similaire au cylindre, le calcul teste l'intersection avec la surface conique et avec le disque de la base.

### Réflexion
Pour simuler des surfaces réfléchissantes, lorsqu'un rayon frappe un objet, on calcule un nouveau rayon réfléchi. Ce nouveau rayon part du point d'impact et sa direction est calculée selon la loi de la réflexion (angle d'incidence = angle de réflexion). La fonction `ft_reflect` se charge de ce calcul.

---

## 🦄️ Détails des Calculs

### Opérations sur les Vecteurs
Les opérations vectorielles sont fondamentales pour tous les calculs.

-   **Addition (`ft_vec_add`)**: `A + B = (Ax + Bx, Ay + By, Az + Bz)`
-   **Soustraction (`ft_vec_sub`)**: `A - B = (Ax - Bx, Ay - By, Az - Bz)`
-   **Multiplication par un scalaire (`ft_vec_scale`)**: `s * A = (s * Ax, s * Ay, s * Az)`
-   **Produit Scalaire (`ft_vec_dot`)**: `A · B = Ax*Bx + Ay*By + Az*Bz`. Le résultat est un scalaire.
-   **Magnitude (`ft_vec_mag`)**: `||A|| = sqrt(A · A)`. Calcule la longueur du vecteur.
-   **Normalisation (`ft_vec_norm`)**: `Â = A / ||A||`. Produit un vecteur de longueur 1.
-   **Produit Vectoriel (`ft_vec_cross`)**: Calcule un vecteur perpendiculaire aux deux vecteurs d'entrée.

### Intersection Rayon-Sphère
-   **Équations**:
    -   Rayon: `P(t) = O + t*D` (O: origine, D: direction)
    -   Sphère: `||P - C|| = r` (C: centre, r: rayon)
-   **Équation à résoudre**: `at² + bt + c = 0`
-   **Coefficients**:
    -   `a = D · D`
    -   `b = 2 * (D · (O - C))`
    -   `c = (O - C) · (O - C) - r²`
-   **Résolution**: On calcule le discriminant `Δ = b² - 4ac`. Si `Δ ≥ 0`, on trouve `t` et on garde la plus petite solution positive.

### Intersection Rayon-Plan
-   **Équations**:
    -   Rayon: `P(t) = O + t*D`
    -   Plan: `(P - P0) · N = 0` (P0: point du plan, N: normale)
-   **Solution**: `t = ((P0 - O) · N) / (D · N)`
-   **Condition**: Une intersection existe si le dénominateur `D · N` n'est pas nul (rayon non parallèle au plan) et si `t > 0`.

### Intersection Rayon-Cylindre
L'intersection est testée en deux parties : le corps et les caps.

1.  **Corps du Cylindre**:
    -   **Équation à résoudre**: `at² + bt + c = 0`
    -   **Coefficients** (V: axe du cylindre, oc: O - C_base):
        -   `a = (D · D) - (D · V)²`
        -   `b = 2 * ((D · oc) - (D · V) * (oc · V))`
        -   `c = (oc · oc) - (oc · V)² - r²`
    -   **Vérification**: Après avoir trouvé `t`, on vérifie que le point d'impact est bien sur la hauteur du cylindre.

2.  **Caps du Cylindre**:
    -   On calcule l'intersection du rayon avec le plan de chaque cap.
    -   On vérifie si le point d'intersection est à l'intérieur du disque du cap (distance au centre < rayon).

La plus petite distance `t` positive parmi toutes les intersections valides est retenue.

### Intersection Rayon-Cône
Similaire au cylindre, on teste le corps et la base.

1.  **Corps du Cône**:
    -   **Équation à résoudre**: `at² + bt + c = 0`
    -   **Coefficients** (V: axe du cône, oc: O - C_sommet, k = (r/h)²):
        -   `a = (D · D) - (1 + k) * (D · V)²`
        -   `b = 2 * ((D · oc) - (1 + k) * (D · V) * (oc · V))`
        -   `c = (oc · oc) - (1 + k) * (oc · V)²`
    -   **Vérification**: On vérifie que le point d'impact est entre le sommet et la base.

2.  **Base du Cône**:
    -   Intersection avec le plan de la base.
    -   Vérification que le point est dans le disque de la base.

La plus petite distance `t` positive est retenue.

### Calcul de la Réflexion (`ft_reflect`)
-   **Formule**: `R = D - 2 * (D · N) * N`
    -   `R`: Vecteur direction réfléchi (normalisé)
    -   `D`: Vecteur direction incident
    -   `N`: Normale à la surface au point d'impact
-   **Implémentation**:
    1.  L'origine du nouveau rayon devient le point d'impact.
    2.  Le vecteur direction du rayon est mis à jour en utilisant la formule ci-dessus.
    3.  Le nouveau vecteur direction est normalisé.